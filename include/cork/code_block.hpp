#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <span>

namespace Cork
{

class CodeBlock final
{
public:
	// Remap the provided address space with read+execute permissions
	static void Protect(std::span<const std::byte> AddressSpan);
	// Remap the provided address space with read+write+execute permissions
	static void UnProtect(std::span<const std::byte> AddressSpan);
	// Invalidate the instruction-cache for the specified region of memory,
	// generally you should use this after you've written memory that you plan
	// to execute
	static void Invalidate(std::span<const std::byte> AddressSpan);

	// Create a codeblock of memory with read+write+execute permissions
	static std::optional<CodeBlock> Create(std::size_t ByteSize);

	const std::span<std::uint32_t> BlockMemory;

	explicit CodeBlock(std::span<std::uint32_t> AddressSpan)
		: BlockMemory(AddressSpan)
	{
	}
	~CodeBlock();

	void Protect() const
	{
		Protect(std::as_bytes(BlockMemory));
	}
	void UnProtect() const
	{
		UnProtect(std::as_bytes(BlockMemory));
	}
	void Invalidate() const
	{
		Invalidate(std::as_bytes(BlockMemory));
	}

	std::span<std::uint32_t> Data() const;
};

} // namespace Cork