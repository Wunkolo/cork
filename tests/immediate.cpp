#include <catch2/catch_test_macros.hpp>

#include <cork/a64/immediate.hpp>

using namespace Cork;

TEST_CASE("BitMaskImmediate64", "[immediate]")
{
	BitMaskImmediate Imm;

	// 2-bit patterns
	Imm = EncodeBitMaskImmediate64(0x5555555555555555).value();
	REQUIRE(Imm.ImmSize == 0b111100);
	REQUIRE(Imm.ImmRotate == 0b000000);
	REQUIRE(Imm.N == false);

	Imm = EncodeBitMaskImmediate64(0xAAAAAAAAAAAAAAAA).value();
	REQUIRE(Imm.ImmSize == 0b111100);
	REQUIRE(Imm.ImmRotate == 0b000001);
	REQUIRE(Imm.N == false);

	// 4-bit patterns
	Imm = EncodeBitMaskImmediate64(0x1111111111111111).value();
	REQUIRE(Imm.ImmSize == 0b111000);
	REQUIRE(Imm.ImmRotate == 0b000000);
	REQUIRE(Imm.N == false);

	Imm = EncodeBitMaskImmediate64(0xEEEEEEEEEEEEEEEE).value();
	REQUIRE(Imm.ImmSize == 0b111010);
	REQUIRE(Imm.ImmRotate == 0b000011);
	REQUIRE(Imm.N == false);

	// 8-bit patterns
	Imm = EncodeBitMaskImmediate64(0x0101010101010101).value();
	REQUIRE(Imm.ImmSize == 0b110000);
	REQUIRE(Imm.ImmRotate == 0b000000);
	REQUIRE(Imm.N == false);

	Imm = EncodeBitMaskImmediate64(0xFEFEFEFEFEFEFEFE).value();
	REQUIRE(Imm.ImmSize == 0b110110);
	REQUIRE(Imm.ImmRotate == 0b000111);
	REQUIRE(Imm.N == false);

	// 16-bit patterns
	Imm = EncodeBitMaskImmediate64(0x0001000100010001).value();
	REQUIRE(Imm.ImmSize == 0b100000);
	REQUIRE(Imm.ImmRotate == 0b000000);
	REQUIRE(Imm.N == false);

	Imm = EncodeBitMaskImmediate64(0xFFFEFFFEFFFEFFFE).value();
	REQUIRE(Imm.ImmSize == 0b101110);
	REQUIRE(Imm.ImmRotate == 0b001111);
	REQUIRE(Imm.N == false);

	// 32-bit patterns
	Imm = EncodeBitMaskImmediate64(0x0000000100000001).value();
	REQUIRE(Imm.ImmSize == 0b000000);
	REQUIRE(Imm.ImmRotate == 0b000000);
	REQUIRE(Imm.N == false);

	Imm = EncodeBitMaskImmediate64(0xFFFFFFFEFFFFFFFE).value();
	REQUIRE(Imm.ImmSize == 0b011110);
	REQUIRE(Imm.ImmRotate == 0b011111);
	REQUIRE(Imm.N == false);

	// 64-bit patterns
	Imm = EncodeBitMaskImmediate64(0x0000000000000001).value();
	REQUIRE(Imm.ImmSize == 0b000000);
	REQUIRE(Imm.ImmRotate == 0b000000);
	REQUIRE(Imm.N == true);

	Imm = EncodeBitMaskImmediate64(0xFFFFFFFFFFFFFFFE).value();
	REQUIRE(Imm.ImmSize == 0b111110);
	REQUIRE(Imm.ImmRotate == 0b111111);
	REQUIRE(Imm.N == true);
}