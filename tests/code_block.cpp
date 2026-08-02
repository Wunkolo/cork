#include <catch2/catch_test_macros.hpp>

#include <cork/code_block.hpp>

#include <array>

using namespace Cork;

#if defined(__ARM64__) || defined(__aarch64__) || defined(_M_ARM64)
// Testing codeblock execution on an a64 host
TEST_CASE("CodeBlock Execute a64", "[code_block]")
{
	const std::array<std::uint32_t, 3> TestCode{{
		0x5297dde0, //  mov	w0, #0xbeef
		0x72bbd5a0, //  movk w0, #0xdead, lsl #16
		0xd65f03c0, //  ret
	}};

	std::optional<CodeBlock> CreateResult
		= CodeBlock::Create(TestCode.size() * sizeof(std::uint32_t));
	REQUIRE(CreateResult.has_value());

	const CodeBlock& Code = CreateResult.value();
	REQUIRE(Code.BlockMemory.data() != nullptr);

	// Copy code over
	std::copy(TestCode.cbegin(), TestCode.cend(), Code.BlockMemory.begin());

	// Remove write access
	Code.Protect();

	// Invalidate i-cache
	Code.Invalidate();

	// Execute!
	const std::size_t Result
		= reinterpret_cast<std::size_t (*)()>(Code.BlockMemory.data())();

	REQUIRE(Result == 0xDEADBEEF);
}

#elif defined(__x86_64__) || defined(_M_AMD64)
// Testing codeblock execution on an x64 host.
TEST_CASE("CodeBlock Execute x64", "[code_block]")
{
	// This is x64 assembly that is awkwardly aligned to 4-bytes
	const std::array<std::uint32_t, 3> TestCode{{
		0xadbeefb8,    // mov eax, 0xdeadbeef
		0x90'90'c3'de, // ret, nop, nop
	}};

	std::optional<CodeBlock> CreateResult
		= CodeBlock::Create(TestCode.size() * sizeof(std::uint32_t));
	REQUIRE(CreateResult.has_value());

	const CodeBlock& Code = CreateResult.value();
	REQUIRE(Code.BlockMemory.data() != nullptr);

	// Copy code over
	std::copy(TestCode.cbegin(), TestCode.cend(), Code.BlockMemory.begin());

	// Remove write access
	Code.Protect();

	// Invalidate i-cache
	Code.Invalidate();

	// Execute!
	const std::size_t Result
		= reinterpret_cast<std::size_t (*)()>(Code.BlockMemory.data())();

	REQUIRE(Result == 0xDEADBEEF);
}
#endif