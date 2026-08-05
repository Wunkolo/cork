#pragma once

#include <array>
#include <bit>
#include <cassert>
#include <cstddef>
#include <cstdint>

namespace Cork
{

template<std::size_t BitSize, std::size_t Alignment = 1>
struct Imm
{
	static_assert(
		std::has_single_bit(Alignment),
		"Alignment must be a positive power of two"
	);

	static constexpr std::uint32_t AlignmentMask = Alignment - 1;
	static constexpr std::uint32_t AlignmentBits = std::popcount(AlignmentMask);
	static constexpr std::uint32_t Mask          = (1 << BitSize) - 1;
	const std::uint32_t            Value;

	constexpr Imm(std::uint32_t ImmValue) : Value(ImmValue)
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

	static constexpr std::uint32_t AlignmentMask = Alignment - 1;
	static constexpr std::uint32_t AlignmentBits = std::popcount(AlignmentMask);
	static constexpr std::uint32_t Mask          = (1 << BitSize) - 1;
	const std::int32_t             Value;

	constexpr SImm(std::int32_t ImmValue) : Value(ImmValue)
	{
		const struct
		{
			std::int32_t i32 : (BitSize + AlignmentBits);
		} SignExtended{.i32 = ImmValue};
		static_assert(sizeof(SignExtended) == sizeof(std::uint32_t));
		// Ensure value can be encoded, maybe do this at encode-time and not in
		// the ctor?
		assert(
			static_cast<std::uint32_t>(SignExtended.i32)
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

} // namespace Cork