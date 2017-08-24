#pragma once
#pragma once
#include "win32_slab.hpp"
#ifdef _WIN32
namespace mcpputil
{
	inline slab_t::slab_t(size_t size, void *addr)
	{
		if (!allocate(size, addr))
			::std::terminate();
	}
	inline slab_t::slab_t(size_t size)
	{
		if (!allocate(size))
			::std::terminate();
	}
	inline slab_t::~slab_t()
	{
		destroy();
	}
	inline void *slab_t::addr() const
	{
		return m_addr;
	}
	inline auto slab_t::size() const -> size_type
	{
		return m_size;
	}
	inline bool slab_t::valid() const
	{
		return m_valid;
	}
	inline uint8_t *slab_t::begin() const noexcept
	{
		return reinterpret_cast<uint8_t *>(m_addr);
	}
	inline uint8_t *slab_t::end() const noexcept
	{
		return reinterpret_cast<uint8_t *>(m_addr) + m_size;
	}
	inline auto slab_t::memory_range() const noexcept->memory_range_t<uint8_t*>
	{
		return { begin(),end() };
	}
}
#endif
