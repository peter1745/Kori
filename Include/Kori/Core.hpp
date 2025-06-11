#pragma once

#include <cstdint>
#include <cstddef>
#include <utility>
#include <concepts>

namespace Kori {

    template<typename T>
    constexpr auto align_up2(T value, uint64_t align) noexcept -> T
    {
        return reinterpret_cast<T>((reinterpret_cast<uint64_t>(value) + (align - 1)) & ~(align - 1));
    }

    template<typename... Ts>
    struct VariantOverloadSet : Ts...
    {
        using Ts::operator()...;
    };

    template<typename... Ts>
    VariantOverloadSet(Ts...) -> VariantOverloadSet<Ts...>;

    template<typename T>
    struct DeferImpl
    {
        T callback;

        DeferImpl(T callback) noexcept
            : callback(std::move(callback))
        {}

        ~DeferImpl() noexcept
        {
            callback();
        }
    };

}

#define KoriConcatImpl(x, y) x##y
#define KoriConcat(x, y) KoriConcatImpl(x, y)

#define KoriDeferWith(...) ::Kori::DeferImpl KoriConcat(kori_defer_obj_, __COUNTER__) = [__VA_ARGS__]()
#define KoriDefer KoriDeferWith(&)
