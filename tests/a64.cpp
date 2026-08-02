#include <catch2/catch_test_macros.hpp>

#include <cork/cork.hpp>

using namespace Cork;

#define TEST_EMIT(HEX, EXPR)                                                   \
	TEST_CASE(#EXPR, "[a64]")                                                  \
	{                                                                          \
		CodeGenerator code;                                                    \
		code.EXPR;                                                             \
		REQUIRE(code.GetCode()[0] == (HEX));                                   \
	}

TEST_EMIT(0x1A0F01C3, ADC(W3, W14, W15))
TEST_EMIT(0x1A1803A5, ADC(W5, W29, W24))
TEST_EMIT(0x1A0F02B3, ADC(W19, W21, W15))
TEST_EMIT(0x9A0101A0, ADC(X0, X13, X1))
TEST_EMIT(0x9A0E01E7, ADC(X7, X15, X14))
TEST_EMIT(0x9A18031E, ADC(X30, X24, X24))
TEST_EMIT(0x3A04030D, ADCS(W13, W24, W4))
TEST_EMIT(0x3A0F0159, ADCS(W25, W10, W15))
TEST_EMIT(0x3A070042, ADCS(W2, W2, W7))
TEST_EMIT(0xBA1003CE, ADCS(X14, X30, X16))
TEST_EMIT(0xBA190368, ADCS(X8, X27, X25))
TEST_EMIT(0xBA0D01E1, ADCS(X1, X15, X13))

TEST_EMIT(0xD503205F, WFE())
TEST_EMIT(0xD503207F, WFI())
TEST_EMIT(0xD503203F, YIELD())