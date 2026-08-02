#include <cork/code_block.hpp>

#if defined(_WIN32)
#define NOMINMAX
#include <windows.h>
#elif defined(__APPLE__)
#include <libkern/OSCacheControl.h> // sys_icache_invalidate
#include <sys/mman.h>
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
#elif defined(__APPLE__)
	pthread_jit_write_protect_np(1);
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
#elif defined(__APPLE__)
	pthread_jit_write_protect_np(0);
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
#elif defined(__APPLE__)
	sys_icache_invalidate(
		const_cast<std::byte*>(AddressSpan.data()), AddressSpan.size()
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
#elif defined(__APPLE__)
	// Note that on MacOS, threads have to be marked to allow write+execute
	// access with pthread_jit_write_protect_np
	NewAddress = static_cast<std::uint32_t*>(mmap(
		nullptr, ByteSize, PROT_READ | PROT_WRITE | PROT_EXEC,
		MAP_ANON | MAP_PRIVATE | MAP_JIT, -1, 0
	));
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

	return std::make_optional<CodeBlock>(
		std::span<std::uint32_t>(NewAddress, InstructionCount)
	);
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