#pragma once

#include <cstdint>

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

} // namespace Cork