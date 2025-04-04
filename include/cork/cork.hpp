#pragma once

#include <cstddef>
#include <cstdint>

#include <optional>
#include <vector>

#include <cork/a64/register.hpp>

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

// Zero register(32-bit)
inline constexpr WzrReg WZR{};
// Zero register(64-bit)
inline constexpr XzrReg ZR{}, XZR{};

// Stack register(32-bit)
inline constexpr WspReg WSP{};
// Stack register(64-bit)
inline constexpr XspReg SP{}, XSP{};

template<typename PolicyT>
class CodeGenerator : public PolicyT
{
public:
	CodeGenerator()
	{
	}

private:
};

} // namespace Cork