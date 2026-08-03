#pragma once

#include <bit>
#include <cassert>
#include <cstddef>
#include <cstdint>

namespace Cork
{

/// Forward declarations
struct WReg;
struct XReg;

// Encoded Register-width
enum class RegisterWidth : std::uint8_t
{
	Width32 = 0,
	Width64 = 1,
	// NEON
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
	// assert(std::has_single_bit(Width));
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

struct Reg
{
	constexpr explicit Reg(std::uint8_t InIndex, std::uint8_t InBitWidth)
		: Index(InIndex), Width(ToRegisterWidth(InBitWidth))
	{
	}

	constexpr explicit Reg(std::uint8_t InIndex, RegisterWidth InWidth)
		: Index(InIndex), Width(InWidth)
	{
	}

	// Register Index 0-31
	// Index 31 may be either the Zero-Register or Stack-Register depending on
	// the context
	const std::uint8_t Index : 5;
	// 1 << BitWidth
	const RegisterWidth Width : 3;
};

// Ideally, keep this type small and very cheap to pass around
static_assert(sizeof(Reg) == sizeof(std::byte));
static_assert(std::is_trivially_copyable_v<Reg>);

struct RReg : public Reg
{
	constexpr explicit RReg(std::uint8_t InIndex, std::uint8_t InBitWidth)
		: Reg(InIndex, InBitWidth)
	{
	}

	constexpr explicit RReg(std::uint8_t InIndex, RegisterWidth InWidth)
		: Reg(InIndex, InWidth)
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
	constexpr explicit WzrReg() : RReg(31, RegisterWidth::Width32)
	{
	}
};

struct XzrReg : public RReg
{
	constexpr explicit XzrReg() : RReg(31, RegisterWidth::Width64)
	{
	}
};

// Stack register
struct WspReg : public RReg
{
	constexpr explicit WspReg() : RReg(31, RegisterWidth::Width32)
	{
	}
};

struct XspReg : public RReg
{
	constexpr explicit XspReg() : RReg(31, RegisterWidth::Width64)
	{
	}
};

// 32-bit general purpose register
struct WReg final : public RReg
{
	constexpr explicit WReg(std::uint8_t InIndex)
		: RReg(InIndex, RegisterWidth::Width32)
	{
	}

	// Implicitly accepts the Zr register as register 31
	constexpr WReg(WzrReg) : RReg(31, RegisterWidth::Width32)
	{
	}
};

// 64-bit general purpose register
struct XReg final : public RReg
{
	constexpr explicit XReg(std::uint8_t InIndex)
		: RReg(InIndex, RegisterWidth::Width64)
	{
	}

	// Implicitly accepts the Zr register as register 31
	constexpr XReg(XzrReg) : RReg(31, RegisterWidth::Width64)
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

/// Filter-types

// Strictly accepts either a general purpose register, or the stack register
struct WRegWsp : public RReg
{
	constexpr WRegWsp(WspReg) : RReg(31, RegisterWidth::Width32)
	{
	}

	constexpr WRegWsp(WReg Wr) : RReg(Wr.Index, RegisterWidth::Width32)
	{
		// Register 31 only available through the stack register type
		assert(Wr.Index != 31);
	}
};

struct XRegSp : public RReg
{
	constexpr XRegSp(XspReg) : RReg(31, RegisterWidth::Width64)
	{
	}

	constexpr XRegSp(XReg Xr) : RReg(Xr.Index, RegisterWidth::Width64)
	{
		// Register 31 only available through the stack register type
		assert(Xr.Index != 31);
	}
};

/// Assembler types
// General purpose registers(32-bit)
inline constexpr WReg W0{0}, W1{1}, W2{2}, W3{3}, W4{4}, W5{5}, W6{6}, W7{7},
	W8{8}, W9{9}, W10{10}, W11{11}, W12{12}, W13{13}, W14{14}, W15{15}, W16{16},
	W17{17}, W18{18}, W19{19}, W20{20}, W21{21}, W22{22}, W23{23}, W24{24},
	W25{25}, W26{26}, W27{27}, W28{28}, W29{29}, W30{30};

// General purpose registers(64-bit)
inline constexpr XReg X0{0}, X1{1}, X2{2}, X3{3}, X4{4}, X5{5}, X6{6}, X7{7},
	X8{8}, X9{9}, X10{10}, X11{11}, X12{12}, X13{13}, X14{14}, X15{15}, X16{16},
	X17{17}, X18{18}, X19{19}, X20{20}, X21{21}, X22{22}, X23{23}, X24{24},
	X25{25}, X26{26}, X27{27}, X28{28}, X29{29}, X30{30};

inline constexpr Condition EQ{Condition::EQ}, NE{Condition::NE},
	CS{Condition::CS}, CC{Condition::CC}, MI{Condition::MI}, PL{Condition::PL},
	VS{Condition::VS}, VC{Condition::VC}, HI{Condition::HI}, LS{Condition::LS},
	GE{Condition::GE}, LT{Condition::LT}, GT{Condition::GT}, LE{Condition::LE},
	AL{Condition::AL}, NV{Condition::NV}, HS{Condition::HS}, LO{Condition::LO};

// Zero register(32-bit)
inline constexpr WzrReg WZR{};
// Zero register(64-bit)
inline constexpr XzrReg ZR{}, XZR{};

// Stack register(32-bit)
inline constexpr WspReg WSP{};
// Stack register(64-bit)
inline constexpr XspReg SP{}, XSP{};

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

} // namespace Cork