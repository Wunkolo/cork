#pragma once

#include <array>
#include <bit>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <optional>

namespace Cork
{

template<std::size_t BitSize, std::size_t Alignment = 1>
struct Imm
{
	static_assert(
		std::has_single_bit(Alignment),
		"Alignment must be a positive power of two"
	);

	static constexpr std::uint64_t AlignmentMask = Alignment - 1;
	static constexpr std::uint64_t AlignmentBits = std::popcount(AlignmentMask);
	static constexpr std::uint64_t Mask          = (1 << BitSize) - 1;
	const std::uint64_t            Value;

	constexpr Imm(std::uint64_t ImmValue) : Value(ImmValue)
	{
		// Ensure value can be encoded, maybe do this at encode-time and not in
		// the ctor?
		assert((ImmValue & Mask) == Value);

		if constexpr( Alignment > 1 )
		{
			// Not aligned
			assert((ImmValue & AlignmentMask) == 0);
		}
	}
};

template<std::size_t BitSize, std::size_t Alignment = 1>
struct SImm
{
	static_assert(
		std::has_single_bit(Alignment),
		"Alignment must be positive power of two"
	);

	static constexpr std::uint64_t AlignmentMask = Alignment - 1;
	static constexpr std::uint64_t AlignmentBits = std::popcount(AlignmentMask);
	static constexpr std::uint64_t Mask          = (1 << BitSize) - 1;
	const std::int64_t             Value;

	constexpr SImm(std::int64_t ImmValue) : Value(ImmValue)
	{
		const struct
		{
			std::int64_t i64 : (BitSize + AlignmentBits);
		} SignExtended{.i64 = ImmValue};
		static_assert(sizeof(SignExtended) == sizeof(std::uint64_t));
		// Ensure value can be encoded, maybe do this at encode-time and not in
		// the ctor?
		assert(
			static_cast<std::uint32_t>(SignExtended.i64)
			== static_cast<std::uint32_t>(ImmValue)
		);

		if constexpr( Alignment > 1 )
		{
			// Not aligned
			assert((ImmValue & AlignmentMask) == 0);
		}
	}
};

template<std::uint8_t... Choices>
struct ImmChoice
{
private:
	consteval std::uint8_t FindChoiceIndex(std::uint8_t Choice)
	{
		// Ensure this is a valid choice among the options
		const bool ValidChoice = ((Choice == Choices) || ...);
		assert(ValidChoice);

		// Get the index of the choice
		constexpr std::array ChoiceArray = {Choices...};
		for( std::size_t i = 0; i < sizeof...(Choices); ++i )
		{
			if( ChoiceArray[i] == Choice )
			{
				return i;
			}
		}

		// Unreachable
		return ~std::uint8_t(0);
	}

public:
	const std::uint32_t Value;

	// Number of bits required to encode all choices
	static constexpr std::size_t BitWidth
		= std::bit_width(sizeof...(Choices) - 1);

	consteval ImmChoice(std::uint8_t ImmValue)
		: Value(FindChoiceIndex(ImmValue))
	{
	}
};

struct BitMaskImmediate
{
	// Size of the pattern, a '0', and then one less than the number of
	// sequential `1` bits within the pattern
	// 11110x =  2bit pattern, `x` encodes up to  1 sequential `1`-bits
	// 1110xx =  4bit pattern, `x` encodes up to  3 sequential `1`-bits
	// 110xxx =  8bit pattern, `x` encodes up to  7 sequential `1`-bits
	// 10xxxx = 16bit pattern, `x` encodes up to 15 sequential `1`-bits
	// 0xxxxx = 32bit pattern, `x` encodes up to 31 sequential `1`-bits
	// xxxxxx = 64bit pattern, `x` encodes up to 63 sequential `1`-bits
	// Ex:
	// N | ImmSize | ImmRotate | Value
	// 0 |  111100 |    000000 | 0101010101...
	// 0 |  111000 |    000000 | 0001000100...
	// 0 |  111100 |    000001 | 1010101010...
	// 0 |  111000 |    000001 | 0000100010...
	// 0 |  111000 |    000010 | 0000010001...
	// 0 |  111000 |    000010 | 0000010001...
	std::uint8_t ImmSize : 6;
	// Number of right-rotations to apply to the pattern
	std::uint8_t ImmRotate : 6;
	// Indicates 64-bit encoding mode
	bool N : 1;
};

// https://kddnewton.com/2022/08/11/aarch64-bitmask-immediates.html
// https://dougallj.wordpress.com/2021/10/30/bit-twiddling-optimising-aarch64-logical-immediate-encoding-and-decoding/
// https://gist.github.com/dougallj/97d8621d4542ba31e004acc8075fac14
constexpr std::optional<BitMaskImmediate>
	EncodeBitMaskImmediate64(std::uint64_t Value64)
{
	// Cannot represent all-`0`/`1`s
	if( Value64 == 0 || (~Value64) == 0 )
	{
		return std::nullopt;
	}

	// Clear the lowest span of `1`s and count `0`s to get the total number of
	// bits between one span of `1`s and the next
	const std::uint64_t Rotation = std::countr_zero(Value64 & (Value64 + 1));

	// Remove the rotation so we have the `1`s in the LSB, and `0`s in the MSB
	// Ex: 00111000 -> 00000111
	// Ex: 11111100 -> 00111111
	// Ex: 11111000 -> 00011111
	const std::uint64_t Normalized = std::rotr(Value64, Rotation);

	// Clear the lowest span of `1`s again to get the total period of the
	// bit-mask pattern. This is guaranteed to be a power of two
	const std::uint64_t PatternSize
		= std::countr_zero(Normalized & (Normalized + 1));
	// Number of active `1`s in the bit-mask pattern.
	const std::uint64_t Ones = std::countr_one(Normalized);

	if( std::rotr(Value64, PatternSize) != Value64 )
	{
		// Not a repeating pattern
		return std::nullopt;
	}

	// Negate the rotation to rotate it back into the original pattern
	const std::uint64_t ImmRotate = -Rotation & (PatternSize - 1);

	// Encode the Size of the pattern, a '0', and one less than the number of
	// continuous `1` bits required in the pattern
	const std::uint64_t ImmSize = ((-PatternSize) << 1) | (Ones - 1);

	// If the Pattern size is 64-bits
	const bool N = PatternSize >= 64;

	return BitMaskImmediate{
		.ImmSize   = static_cast<std::uint8_t>(ImmSize),
		.ImmRotate = static_cast<std::uint8_t>(ImmRotate),
		.N         = N,
	};
}

constexpr std::optional<BitMaskImmediate>
	EncodeBitMaskImmediate32(std::uint32_t Value32)
{
	const std::uint64_t Value64
		= (static_cast<std::uint64_t>(Value32) << 32) | Value32;
	return EncodeBitMaskImmediate64(Value64);
}

struct BitMask32
{
private:
public:
	std::uint32_t Value;

	constexpr BitMask32(Imm<6> ImmSize, Imm<6> ImmRotation)
		: Value((ImmSize.Value << 6) | ImmRotation.Value)
	{
	}

	constexpr BitMask32(std::uint32_t ImmValue)
	{
		const std::optional<BitMaskImmediate> EncodeResult
			= EncodeBitMaskImmediate32(ImmValue);
		// Value could not be encoded as a BitMaskImmediate
		assert(EncodeResult.has_value());

		const BitMaskImmediate BitImm = *EncodeResult;
		// Value requires a 64-bit representation
		assert(BitImm.N == 0);

		Value = (BitImm.ImmRotate << 6) | BitImm.ImmSize;
	}
};

struct BitMask64
{
private:
public:
	std::uint32_t Value;

	constexpr BitMask64(bool N, Imm<6> ImmSize, Imm<6> ImmRotation)
		: Value((N << 12) | (ImmSize.Value << 6) | ImmRotation.Value)
	{
	}

	constexpr BitMask64(std::uint64_t ImmValue)
	{
		const std::optional<BitMaskImmediate> EncodeResult
			= EncodeBitMaskImmediate64(ImmValue);
		// Value could not be encoded as a BitMaskImmediate
		assert(EncodeResult.has_value());

		const BitMaskImmediate BitImm = *EncodeResult;

		Value = (BitImm.N << 12) | (BitImm.ImmRotate << 6) | BitImm.ImmSize;
	}
};

} // namespace Cork