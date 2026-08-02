#include <cork/code_block.hpp>

#if defined(_WIN32)
#define NOMINMAX
#include <windows.h>
#else
#include <sys/mman.h>
#endif

namespace Cork
{

void CodeBlock::Protect(std::span<const std::byte> AddressSpan)
{
#if defined(_WIN32)
	DWORD OldProtect;
	VirtualProtect(
		const_cast<std::byte*>(AddressSpan.data()), AddressSpan.size(),
		PAGE_EXECUTE_READ, &OldProtect
	);
#else
	mprotect(
		const_cast<std::byte*>(AddressSpan.data()), AddressSpan.size(),
		PROT_READ | PROT_EXEC
	);
#endif
}

void CodeBlock::UnProtect(std::span<const std::byte> AddressSpan)
{
#if defined(_WIN32)
	DWORD OldProtect;
	VirtualProtect(
		const_cast<std::byte*>(AddressSpan.data()), AddressSpan.size(),
		PAGE_EXECUTE_READWRITE, &OldProtect
	);
#else
	mprotect(
		const_cast<std::byte*>(AddressSpan.data()), AddressSpan.size(),
		PROT_READ | PROT_WRITE
	);
#endif
}
void CodeBlock::Invalidate(std::span<const std::byte> AddressSpan)
{
#if defined(_WIN32)
	FlushInstructionCache(
		GetCurrentProcess(), AddressSpan.data(), AddressSpan.size()
	);
#else
	__builtin___clear_cache(
		const_cast<std::byte*>(AddressSpan.data()),
		const_cast<std::byte*>(AddressSpan.data() + AddressSpan.size())
	);
#endif
}

std::optional<CodeBlock> CodeBlock::Create(std::size_t ByteSize)
{
	// Align address to 4-byte instructions
	ByteSize                           = (ByteSize + 3) & ~3;
	const std::size_t InstructionCount = ByteSize / 4;

	std::uint32_t* NewAddress = nullptr;

#if defined(_WIN32)
	NewAddress = static_cast<std::uint32_t*>(
		VirtualAlloc(nullptr, ByteSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE)
	);
#else
	NewAddress = static_cast<std::uint32_t*>(mmap(
		nullptr, ByteSize, PROT_READ | PROT_WRITE | PROT_EXEC,
		MAP_ANON | MAP_PRIVATE, -1, 0
	));
#endif
	if( NewAddress == nullptr )
	{
		return std::nullopt;
	}

	return CodeBlock(std::span<std::uint32_t>(NewAddress, InstructionCount));
}

CodeBlock::~CodeBlock()
{
	if( BlockMemory.data() != nullptr )
	{
#if defined(_WIN32)
		VirtualFree(BlockMemory.data(), 0, MEM_RELEASE);
#else
		munmap(BlockMemory.data(), BlockMemory.size());
#endif
	}
}

} // namespace Cork