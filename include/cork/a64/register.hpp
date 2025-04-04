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

enum class RegisterWidth : std::uint8_t
{
	Width32 = 0,
	Width64 = 1,
	// AdvSIMD
	Width128 = 2,
	// SVE
	Width256  = 3,
	Width512  = 4,
	Width1024 = 5,
	Width2048 = 6,
	MAX,
};
// Must fit within 3 bits
static_assert(static_cast<std::uint8_t>(RegisterWidth::MAX) <= 0b111);

// Convert from a register bit-count into an encoded RegisterWidth
constexpr RegisterWidth ToRegisterWidth(std::uint16_t Width)
{
	assert(std::has_single_bit(Width));
	return static_cast<enum RegisterWidth>(std::bit_width(Width) - 6);
}

static_assert(ToRegisterWidth(32) == RegisterWidth::Width32);
static_assert(ToRegisterWidth(64) == RegisterWidth::Width64);
static_assert(ToRegisterWidth(128) == RegisterWidth::Width128);
static_assert(ToRegisterWidth(256) == RegisterWidth::Width256);
static_assert(ToRegisterWidth(512) == RegisterWidth::Width512);
static_assert(ToRegisterWidth(1024) == RegisterWidth::Width1024);
static_assert(ToRegisterWidth(2048) == RegisterWidth::Width2048);

// Convert from the encoded register-width into an actual bit-count
constexpr std::uint16_t RegisterBits(RegisterWidth Width)
{
	return 1 << (static_cast<std::uint8_t>(Width) + 5);
}
static_assert(RegisterBits(RegisterWidth::Width32) == 32);
static_assert(RegisterBits(RegisterWidth::Width64) == 64);
static_assert(RegisterBits(RegisterWidth::Width128) == 128);
static_assert(RegisterBits(RegisterWidth::Width256) == 256);
static_assert(RegisterBits(RegisterWidth::Width512) == 512);
static_assert(RegisterBits(RegisterWidth::Width1024) == 1024);
static_assert(RegisterBits(RegisterWidth::Width2048) == 2048);

struct WzrReg;
struct XzrReg;

struct Reg
{
	constexpr explicit Reg(std::uint8_t InIndex, std::uint8_t InBitWidth)
		: Index(InIndex), Width(ToRegisterWidth(InBitWidth))
	{
	}

	// Register Index 0-31
	// Index 31 may be either the Zero-Register or Stack-Register depending on
	// the context
	const std::uint8_t Index : 5;
	// 1 << BitWidth
	const RegisterWidth Width : 3;
};
static_assert(sizeof(Reg) == sizeof(std::byte));

struct RReg : public Reg
{
	constexpr explicit RReg(std::uint8_t InIndex, std::uint8_t InBitWidth)
		: Reg(InIndex, InBitWidth)
	{
	}

	[[nodiscard]] XReg ToX() const;
	[[nodiscard]] WReg ToW() const;
};

// In some cases, register 31 is the zero-register, or the stack register.
// Strict typing is used to enforce either case

// Zero-register

struct WzrReg : public RReg
{
	constexpr explicit WzrReg() : RReg(32, 31)
	{
	}
};

struct XzrReg : public RReg
{
	constexpr explicit XzrReg() : RReg(64, 31)
	{
	}
};

// Stack register
struct WspReg : public RReg
{
	constexpr explicit WspReg() : RReg(64, 31)
	{
	}
};

struct XspReg : public RReg
{
	constexpr explicit XspReg() : RReg(64, 31)
	{
	}
};

// 32-bit general purpose register
struct WReg final : public RReg
{
	constexpr explicit WReg(std::uint8_t InIndex) : RReg(InIndex, 32)
	{
	}

	// Implicitly accepts the Zr register as register 31
	constexpr WReg(WzrReg) : RReg(31, 32)
	{
	}
};

// 64-bit general purpose register
struct XReg final : public RReg
{
	constexpr explicit XReg(std::uint8_t InIndex) : RReg(InIndex, 64)
	{
	}

	// Implicitly accepts the Zr register as register 31
	constexpr XReg(XzrReg) : RReg(31, 64)
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

// Filter-types

// Strictly accepts either a general purpose register, or the stack register
struct WRegWsp : public RReg
{
	constexpr WRegWsp(WspReg) : RReg(32, 31)
	{
	}

	constexpr WRegWsp(WReg Wr) : RReg(32, Wr.Index)
	{
		// Register 31 only available through the stack register type
		assert(Wr.Index != 31);
	}
};

struct XRegSp : public RReg
{
	constexpr XRegSp(XspReg) : RReg(64, 31)
	{
	}

	constexpr XRegSp(XReg Xr) : RReg(64, Xr.Index)
	{
		// Register 31 only available through the stack register type
		assert(Xr.Index != 31);
	}
};

} // namespace Cork