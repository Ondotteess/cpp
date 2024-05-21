#include <iostream>
#include <cassert>
#include "ScopedPointer.cpp"


struct TestData {
    int value;

    TestData(int val) : value(val) {}
};

int main() {
    // Deep
    {
        // ctr
        ScopedPointerDeep<TestData> ptr1(new TestData(10));
        assert(ptr1->value == 10);

        // copy ctrs
        ScopedPointerDeep<TestData> ptr2(ptr1);
        assert(ptr2->value == 10);
        assert(ptr1->value == 10);

        // move ctrs
        ScopedPointerDeep<TestData> ptr3(std::move(ptr1));
        assert(ptr3->value == 10);
        assert(ptr1.operator->() == nullptr); // ptr1 should be empty

        // copy assignment op
        ScopedPointerDeep<TestData> ptr4(new TestData(20));
        ptr4 = ptr2;
        assert(ptr4->value == 10);

        // self assigment
        ptr4 = ptr4;
    }

    // transfer
    {
        // ctr
        ScopedPointerTransfer<TestData> ptr1(new TestData(10));
        assert(ptr1->value == 10);

        // move
        ScopedPointerTransfer<TestData> ptr2(std::move(ptr1));
        assert(ptr2->value == 10);
        assert(ptr1.operator->() == nullptr); // should be empty

        // move assignment operator
        ScopedPointerTransfer<TestData> ptr3(new TestData(20));
        ptr3 = std::move(ptr2);
        assert(ptr3->value == 10);
        assert(ptr2.operator->() == nullptr); // should be empty
    }

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
