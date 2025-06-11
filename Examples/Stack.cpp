#include <Kori/Stack.hpp>

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

    std::println("Used: {} bytes", Kori::stack_allocator().used_size());
    auto* test_obj_1 = Kori::stack_construct<TestObject>(15);
    (void)test_obj_1;
    std::println("Used: {} bytes", Kori::stack_allocator().used_size());

    {
        KoriStackFrame();
        std::println("Used: {} bytes", Kori::stack_allocator().used_size());
        auto* test_obj = Kori::stack_construct<TestObject>(5);
        (void)test_obj;
        std::println("Used: {} bytes", Kori::stack_allocator().used_size());
    }

    std::println("Used: {} bytes", Kori::stack_allocator().used_size());
    return 0;
}
