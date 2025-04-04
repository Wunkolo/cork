#pragma once

#include <bit>
#include <cassert>
#include <cstddef>
#include <cstdint>

namespace Cork
{

// Forward declarations
struct WReg;
struct XReg;

// Register-types
struct Reg
{
	constexpr explicit Reg(
		std::int8_t InIndex, std::uint8_t InBitWidth, bool InIsVector
	)
		: Index(InIndex), BitWidth(InBitWidth), IsVector(InIsVector)
	{
		assert(InIndex >= -1 && InIndex <= 31);
		assert(
			InBitWidth != 0 && std::has_single_bit(InBitWidth)
			&& "Invalid BitSize"
		);
	}

	const std::int8_t  Index;
	const std::uint8_t BitWidth;
	const bool         IsVector;
};

struct RReg : public Reg
{
	constexpr explicit RReg(std::int8_t InIndex, std::uint8_t InBitWidth)
		: Reg(InIndex, InBitWidth, false)
	{
	}

	[[nodiscard]] XReg ToX() const;
	[[nodiscard]] WReg ToW() const;
};

// 32-bit general purpose register
struct WReg final : public RReg
{
	constexpr explicit WReg(std::int8_t InIndex) : RReg(InIndex, 32)
	{
	}
};

// 64-bit general purpose register
struct XReg final : public RReg
{
	constexpr explicit XReg(std::int8_t InIndex) : RReg(InIndex, 64)
	{
	}
};

inline WReg RReg::ToW() const
{
	return WReg(Index);
}

inline XReg RReg::ToX() const
{
	return XReg(Index);
}

} // namespace Cork