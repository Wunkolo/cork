#pragma once

#include <cstdint>
#include <type_traits>

namespace Cork
{

enum class Condition : std::uint8_t
{
	EQ = 0,  // Equal | Z==1
	NE = 1,  // Not equal | Z==0
	CS = 2,  // Unsigned higher or same (or carry set) | C==1
	CC = 3,  // Unsigned lower (or carry clear) | C==0
	MI = 4,  // Negative. The mnemonic stands for "minus" | N==1
	PL = 5,  // Positive or zero. The mnemonic stands for "plus | N==0
	VS = 6,  // Signed overflow. The mnemonic stands for "V set | V==1
	VC = 7,  // No signed overflow. The mnemonic stands for "V clear" | V==0
	HI = 8,  // Unsigned higher | (C==1) && (Z==0)
	LS = 9,  // Unsigned lower or same | (C==0) || (Z==1)
	GE = 10, // Signed greater than or equal | N==V
	LT = 11, // Signed less than | N!=V
	GT = 12, // Signed greater than | (Z==0) && (N==V)
	LE = 13, // Signed less than or equal | (Z==1) || (N!=V)
	AL = 14, // Always
	NV = 15, // Never

	HS = CS,
	LO = CC,
};

constexpr Condition Invert(Condition BaseCondition)
{
	return static_cast<Condition>(
		static_cast<std::underlying_type_t<Condition>>(BaseCondition) ^ 1
	);
}

enum class ConditionFlag : std::uint8_t
{
	V    = 0b0001,
	C    = 0b0010,
	CV   = 0b0011,
	Z    = 0b0100,
	ZV   = 0b0101,
	ZC   = 0b0110,
	ZCV  = 0b0111,
	N    = 0b1000,
	NV   = 0b1001,
	NC   = 0b1010,
	NCV  = 0b1011,
	NZ   = 0b1100,
	NZV  = 0b1101,
	NZC  = 0b1110,
	NZCV = 0b1111,
};

enum class RegisterExtension : std::uint8_t
{
	UXTB = 0b000,
	UXTH = 0b001,
	UXTW = 0b010, // 32-bit LSL
	UXTX = 0b011, // 64-bit LSL
	SXTB = 0b100,
	SXTH = 0b101,
	SXTW = 0b110,
	SXTX = 0b111,
};

enum class Shift : std::uint8_t
{
	LSL = 0b00,
	LSR = 0b01,
	ASR = 0b10,
	ROR = 0b11,
};

enum class BarrierOperation : std::uint8_t
{
	// Full system is the required shareability domain, reads and writes are the
	// required access types, both before and after the barrier instruction.
	// This option is referred to as the full system barrier.
	SY = 0b1111,
	// Full system is the required shareability domain, writes are the required
	// access type, both before and after the barrier instruction.
	ST = 0b1110,
	// Full system is the required shareability domain, reads are the required
	// access type before the barrier instruction, and reads and writes are the
	// required access types after the barrier instruction.
	LD = 0b1101,
	// Inner Shareable is the required shareability domain, reads and writes are
	// the required access types, both before and after the barrier instruction.
	ISH = 0b1011,
	// Inner Shareable is the required shareability domain, writes are the
	// required access type, both before and after the barrier instruction.
	ISHST = 0b1010,
	// Inner Shareable is the required shareability domain, reads are the
	// required access type before the barrier instruction, and reads and writes
	// are the required access types after the barrier instruction.
	ISHLD = 0b1001,
	// Non-shareable is the required shareability domain, reads and writes are
	// the required access, both before and after the barrier instruction.
	NSH = 0b0111,
	// Non-shareable is the required shareability domain, writes are the
	// required access type, both before and after the barrier instruction.
	NSHST = 0b0110,
	// Non-shareable is the required shareability domain, reads are the required
	// access type before the barrier instruction, and reads and writes are the
	// required access types after the barrier instruction.
	NSHLD = 0b0101,
	// Outer Shareable is the required shareability domain, reads and writes are
	// the required access types, both before and after the barrier instruction.
	OSH = 0b0011,
	// Outer Shareable is the required shareability domain, writes are the
	// required access type, both before and after the barrier instruction.
	OSHST = 0b0010,
	// Outer Shareable is the required shareability domain, reads are the
	// required access type before the barrier instruction, and reads and writes
	// are the required access types after the barrier instruction.
	OSHLD = 0b0001,
};

} // namespace Cork