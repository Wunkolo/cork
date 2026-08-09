#pragma once

#include <cork/a64/enum.hpp>
#include <cork/a64/immediate.hpp>
#include <cork/a64/register.hpp>

#include <algorithm>
#include <bit>
#include <span>
#include <vector>

namespace Cork
{

template<size_t N>
struct StringLiteral
{
	constexpr StringLiteral(const char (&Literal)[N])
	{
		std::copy_n(Literal, N, String);
	}

	static constexpr std::size_t Strlen = N - 1;
	static constexpr std::size_t Size   = N;

	char String[N];
};

// Given a Haystack string literal and Needle characters, build a bit-mask of
// the found elements.
// Ex:
// SplatMask32<"01iii101ddd0", "1"> == 010001010000
// SplatMask32<"01iii101ddd0", "i"> == 001110000000
// SplatMask32<"01iii101ddd0", "d"> == 000000001110
template<StringLiteral<33> HayStack, StringLiteral Needles>
consteval std::uint32_t SplatMask32()
{
	std::uint32_t Result = 0;
	for( std::size_t HaystackIndex = 0; HaystackIndex < 32; HaystackIndex++ )
	{
		for( std::size_t NeedleIndex = 0; NeedleIndex < Needles.Strlen;
			 NeedleIndex++ )
		{
			if( HayStack.String[HaystackIndex] == Needles.String[NeedleIndex] )
			{
				Result |= 1 << (31 - HaystackIndex);
			}
		}
	}
	return Result;
}

// Distribute bits of a value according to the bit-mask
// similar to the `pdep` instruction from BMI
// Keep an eye on this `bit_expand` proposal:
// https://eisenwave.github.io/cpp-proposals/bit-permutations.html#intro-bit-expand
template<std::uint32_t BitMask>
static constexpr std::uint32_t BitExpand(std::uint32_t BitValue) noexcept
{
	static_assert(BitMask);
	// Attempt to detect if this is a continous span of bits
	constexpr std::uint32_t FirstSetBit    = std::countr_zero(BitMask);
	constexpr std::uint32_t BitMaskShifted = BitMask >> FirstSetBit;

	if constexpr( std::countr_one(BitMaskShifted) == std::popcount(BitMask) )
	{
		// Consecutive bits can use simpler masking and shifting
		return (BitValue & BitMaskShifted) << FirstSetBit;
	}

	std::uint32_t Result = 0;
	for( std::uint8_t MaskBitIndex = 0, SourceBitIndex = 0; MaskBitIndex < 32;
		 ++MaskBitIndex )
	{
		const bool MaskBit = (BitMask >> MaskBitIndex) & 1u;
		Result |= (MaskBit & (BitValue >> SourceBitIndex)) << MaskBitIndex;
		SourceBitIndex += MaskBit;
	}
	return Result;
}

// Each possible input argument to an instruction will need a specialized
// `Encode` function to splat its value across the specified bits.

template<std::uint32_t Splat>
inline std::uint32_t Encode(std::uint32_t Value)
{
	return BitExpand<Splat>(Value);
}

template<std::uint32_t Splat>
inline std::uint32_t Encode(RReg Value)
{
	static_assert(static_cast<std::size_t>(std::popcount(Splat)) == 5);
	return BitExpand<Splat>(static_cast<std::uint32_t>(Value.Index));
}

template<std::uint32_t Splat>
inline std::uint32_t Encode(WReg Value)
{
	static_assert(static_cast<std::size_t>(std::popcount(Splat)) == 5);
	return BitExpand<Splat>(static_cast<std::uint32_t>(Value.Index));
}

template<std::uint32_t Splat>
inline std::uint32_t Encode(WRegWsp Value)
{
	static_assert(static_cast<std::size_t>(std::popcount(Splat)) == 5);
	return BitExpand<Splat>(static_cast<std::uint32_t>(Value.Index));
}

template<std::uint32_t Splat>
inline std::uint32_t Encode(XReg Value)
{
	static_assert(static_cast<std::size_t>(std::popcount(Splat)) == 5);
	return BitExpand<Splat>(static_cast<std::uint32_t>(Value.Index));
}

template<std::uint32_t Splat>
inline std::uint32_t Encode(XRegSp Value)
{
	static_assert(static_cast<std::size_t>(std::popcount(Splat)) == 5);
	return BitExpand<Splat>(static_cast<std::uint32_t>(Value.Index));
}

template<std::uint32_t Splat>
inline std::uint32_t Encode(Condition Value)
{
	static_assert(static_cast<std::size_t>(std::popcount(Splat)) == 4);
	return BitExpand<Splat>(static_cast<std::uint32_t>(Value));
}

template<std::uint32_t Splat>
inline std::uint32_t Encode(ConditionFlag Value)
{
	static_assert(static_cast<std::size_t>(std::popcount(Splat)) == 4);
	return BitExpand<Splat>(static_cast<std::uint32_t>(Value));
}

template<std::uint32_t Splat>
inline std::uint32_t Encode(RegisterExtension Value)
{
	static_assert(static_cast<std::size_t>(std::popcount(Splat)) == 3);
	return BitExpand<Splat>(static_cast<std::uint32_t>(Value));
}

template<std::uint32_t Splat>
inline std::uint32_t Encode(Shift Value)
{
	static_assert(static_cast<std::size_t>(std::popcount(Splat)) == 2);
	return BitExpand<Splat>(static_cast<std::uint32_t>(Value));
}

template<std::uint32_t Splat>
inline std::uint32_t Encode(BarrierOperation Value)
{
	static_assert(static_cast<std::size_t>(std::popcount(Splat)) == 4);
	return BitExpand<Splat>(static_cast<std::uint32_t>(Value));
}

template<std::uint32_t Splat>
inline std::uint32_t Encode(InstructionCacheOperation Value)
{
	static_assert(static_cast<std::size_t>(std::popcount(Splat)) == 10);
	return BitExpand<Splat>(static_cast<std::uint32_t>(Value));
}

template<std::uint32_t Splat, std::size_t BitWidth, std::size_t Alignment>
inline std::uint32_t Encode(Imm<BitWidth, Alignment> Value)
{
	static_assert(static_cast<std::size_t>(std::popcount(Splat)) >= BitWidth);
	return BitExpand<Splat>(
		static_cast<std::uint32_t>(Value.Value / Alignment)
	);
}

template<std::uint32_t Splat, std::size_t BitWidth, std::size_t Alignment>
inline std::uint32_t Encode(SImm<BitWidth, Alignment> Value)
{
	static_assert(static_cast<std::size_t>(std::popcount(Splat)) >= BitWidth);
	return BitExpand<Splat>(
		static_cast<std::uint32_t>(Value.Value / Alignment)
	);
}

template<std::uint32_t Splat, std::uint8_t... Choices>
inline std::uint32_t Encode(ImmChoice<Choices...> Value)
{
	static_assert(
		static_cast<std::size_t>(std::popcount(Splat)) >= ImmChoice<Choices...>::BitWidth,
		"Not enough bits to encode choices"
	);
	return BitExpand<Splat>(static_cast<std::uint32_t>(Value.Value));
}

template<std::uint32_t Splat>
inline std::uint32_t Encode(BitMask32 Value)
{
	static_assert(static_cast<std::size_t>(std::popcount(Splat)) >= 12);
	return BitExpand<Splat>(static_cast<std::uint32_t>(Value.Value));
}

template<std::uint32_t Splat>
inline std::uint32_t Encode(BitMask64 Value)
{
	static_assert(static_cast<std::size_t>(std::popcount(Splat)) >= 13);
	return BitExpand<Splat>(static_cast<std::uint32_t>(Value.Value));
}

// In general, it's expected that CodeGenerator does not hold onto any state
// and instead is a re-usable buffer for emitting position-independent code,
// that is then copied over into actual executable memory.
class CodeGenerator
{
private:
	std::vector<std::uint32_t> Instructions;

	// Emit a 32-bit instruction using the provided
	// string-literal bit-pattern, bit-arguments, and argument-values
	// Ex:
	// Emit<"000100010siiiiiiiiiiiinnnnnddddd", "d", "n", "si">(Wd, Wn, Imm);
	// `d` bits will be replaced with `Wd`
	// `n` bits will be replaced with `Wn`
	// `s` and `i` bits will be replaced with `Imm`
	template<
		StringLiteral BitPattern, StringLiteral... BitArguments,
		typename... ArgumentsT>
	inline void Emit(ArgumentsT... Arguments)
	{
		constexpr std::uint32_t StaticBits = SplatMask32<BitPattern, "1">();

		// Encode each argument according to it's splat mask
		const std::uint32_t Encoding
			= (StaticBits | ...
			   | Encode<SplatMask32<BitPattern, BitArguments>()>(
				   std::forward<ArgumentsT>(Arguments)
			   ));

		Instructions.emplace_back(Encoding);
	}

public:
	CodeGenerator() = default;

#include <cork/a64/instructions/a64-base.inc.hpp>

	std::span<const std::uint32_t> GetCode() const
	{
		return Instructions;
	}
};

} // namespace Cork