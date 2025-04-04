#pragma once

#include <cstddef>
#include <cstdint>

#include <algorithm>
#include <array>
#include <span>
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
	std::uint32_t result = 0;
	for( std::size_t i = 0; i < 32; i++ )
	{
		for( std::size_t j = 0; j < Needles.Strlen; j++ )
		{
			if( HayStack.String[i] == Needles.String[j] )
			{
				result |= 1 << (31 - i);
			}
		}
	}
	return result;
}

// Distribute bits of a value according to the bit-mask
// similar to the `pdep` instruction from BMI
// Keep an eye on this `bit_expand` proposal:
// https://eisenwave.github.io/cpp-proposals/bit-permutations.html#intro-bit-expand
template<std::uint32_t BitMask>
static constexpr std::uint32_t BitExpand(std::uint32_t BitValue) noexcept
{
	std::uint32_t result = 0;
	for( std::uint8_t i = 0, j = 0; i < 32; ++i )
	{
		const bool MaskBit = (BitMask >> i) & 1u;
		result |= (MaskBit & (BitValue >> j)) << i;
		j += MaskBit;
	}
	return result;
}

template<std::uint32_t Splat>
std::uint32_t Encode(WReg Value)
{
	static_assert(std::popcount(Splat) == 5);
	return BitExpand<Splat>(static_cast<std::uint32_t>(Value.Index));
}

template<std::uint32_t Splat>
std::uint32_t Encode(XReg Value)
{
	static_assert(std::popcount(Splat) == 5);
	return BitExpand<Splat>(static_cast<std::uint32_t>(Value.Index));
}
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
	void Emit(ArgumentsT... Arguments)
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

	/// @brief Add with Carry.
	/// @note ADC_32_addsub_carry
	/// @param Wd Is the 32-bit name of the general-purpose destination
	/// register, encoded in the "Rd" field.
	/// @param Wn Is the 32-bit name of the first general-purpose source
	/// register, encoded in the "Rn" field.
	/// @param Wm Is the 32-bit name of the second general-purpose source
	/// register, encoded in the "Rm" field.
	void ADC(WReg Wd, WReg Wn, WReg Wm)
	{
		Emit<"00011010000mmmmm000000nnnnnddddd", "d", "n", "m">(Wd, Wn, Wm);
	}

	/// @brief Add with Carry.
	/// @note ADC_64_addsub_carry
	/// @param Xd Is the 64-bit name of the general-purpose destination
	/// register, encoded in the "Rd" field.
	/// @param Xn Is the 64-bit name of the first general-purpose source
	/// register, encoded in the "Rn" field.
	/// @param Xm Is the 64-bit name of the second general-purpose source
	/// register, encoded in the "Rm" field.
	void ADC(XReg Xd, XReg Xn, XReg Xm)
	{
		Emit<"10011010000mmmmm000000nnnnnddddd", "d", "n", "m">(Xd, Xn, Xm);
	}

	/// @brief Add with Carry, setting flags.
	/// @note ADC_32_addsub_carry
	/// @param Wd Is the 32-bit name of the general-purpose destination
	/// register, encoded in the "Rd" field.
	/// @param Wn Is the 32-bit name of the first general-purpose source
	/// register, encoded in the "Rn" field.
	/// @param Wm Is the 32-bit name of the second general-purpose source
	/// register, encoded in the "Rm" field.
	void ADCS(WReg Wd, WReg Wn, WReg Wm)
	{
		Emit<"00111010000mmmmm000000nnnnnddddd", "d", "n", "m">(Wd, Wn, Wm);
	}

	/// @brief Add with Carry, setting flags.
	/// @note ADC_64_addsub_carry
	/// @param Xd Is the 64-bit name of the general-purpose destination
	/// register, encoded in the "Rd" field.
	/// @param Xn Is the 64-bit name of the first general-purpose source
	/// register, encoded in the "Rn" field.
	/// @param Xm Is the 64-bit name of the second general-purpose source
	/// register, encoded in the "Rm" field.
	void ADCS(XReg Xd, XReg Xn, XReg Xm)
	{
		Emit<"10111010000mmmmm000000nnnnnddddd", "d", "n", "m">(Xd, Xn, Xm);
	}

	std::span<const std::uint32_t> GetCode() const
	{
		return Instructions;
	}
};

} // namespace Cork