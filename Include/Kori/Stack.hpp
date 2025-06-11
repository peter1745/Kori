#pragma once

#include <memory>

#include "Core.hpp"

namespace Kori {

    struct StackAllocator
    {
        uint8_t* ptr;
        uint8_t* begin;
        uint8_t* end;

        static constexpr size_t StackSize = 64 * 1024 * 1024;

        StackAllocator()
            : ptr(new uint8_t[StackSize]), begin(ptr), end(ptr + StackSize)
        {
        }

        ~StackAllocator()
        {
            delete[] ptr;
        }

        [[nodiscard]]
        auto used_size() const noexcept -> size_t
        {
            return static_cast<size_t>(std::distance(begin, ptr));
        }
    };

    inline auto stack_allocator() -> StackAllocator&
    {
        thread_local StackAllocator Allocator;
        return Allocator;
    }

    template<typename T>
    auto stack_alloc(size_t count) -> T*
    {
        auto& stack = stack_allocator();
        auto* ptr = reinterpret_cast<T*>(stack.ptr);
        stack.ptr = align_up2(stack.ptr + sizeof(T) * count, 16);
        return ptr;
    }

    template<typename T, typename... Args>
    requires(std::constructible_from<T, Args...>)
    auto stack_construct(Args&&... args) -> T*
    {
        auto* obj = stack_alloc<T>(1);
        std::construct_at(obj, std::forward<Args>(args)...);
        return obj;
    }

}

#define KoriStackFrame() KoriDeferWith(ptr = Kori::stack_allocator().ptr) \
{                                                                           \
   Kori::stack_allocator().ptr = ptr;                                       \
}
