#include <kori/stack.hpp>

#include <print>

struct TestObject
{
    int32_t value;

    TestObject(int32_t value)
        : value(value) {}
};

int main()
{
    KoriStackFrame();

    std::println("Used: {} bytes", kori::stack_allocator().used_size());
    auto* test_obj_1 = kori::stack_construct<TestObject>(15);
    std::println("Used: {} bytes", kori::stack_allocator().used_size());

    {
        KoriStackFrame();
        std::println("Used: {} bytes", kori::stack_allocator().used_size());
        auto* test_obj = kori::stack_construct<TestObject>(5);
        std::println("Used: {} bytes", kori::stack_allocator().used_size());
    }

    std::println("Used: {} bytes", kori::stack_allocator().used_size());
    return 0;
}
