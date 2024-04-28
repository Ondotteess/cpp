#include <iostream>
#include <cassert>
#include "ScopedPointer.cpp"


struct TestData {
    int value;

    TestData(int val) : value(val) {}
};

int main() {
    // ScopedPointerDeep
    {
        ScopedPointerDeep<TestData> deepPtr(new TestData(42));
        ScopedPointerDeep<TestData> deepPtr2 = deepPtr; 

        assert(deepPtr->value == 42);
        assert(deepPtr2->value == 42);

        deepPtr2->value = 100;
        assert(deepPtr->value == 42); // not affected
        assert(deepPtr2->value == 100);

        ScopedPointerDeep<TestData> deepPtr3;
        deepPtr3 = deepPtr2; // Assignment operator

        assert(deepPtr3->value == 100);

        ScopedPointerDeep<TestData> deepPtr4(std::move(deepPtr3)); // Move constructor
        assert(deepPtr4->value == 100);
        assert(deepPtr3.operator->() == nullptr);

        ScopedPointerDeep<TestData> deepPtr5;
        deepPtr5 = std::move(deepPtr4); // Move assignment operator
        assert(deepPtr5->value == 100);
         assert(deepPtr4.operator->() == nullptr); // should be null
    }

    // ScopedPointerTransfer
    {
        ScopedPointerTransfer<TestData> transferPtr(new TestData(42));
        // ScopedPointerTransfer<TestData> transferPtr2 = transferPtr; // Compile error

        assert(transferPtr->value == 42);

        ScopedPointerTransfer<TestData> transferPtr3(std::move(transferPtr)); // Move constructor
        assert(transferPtr3->value == 42);
        assert(transferPtr.operator->() == nullptr); // should be null

        ScopedPointerTransfer<TestData> transferPtr4;
        transferPtr4 = std::move(transferPtr3); // Move assignment operator
        assert(transferPtr4->value == 42);
        assert(transferPtr3.operator->() == nullptr); // hould be null
    }

    std::cout << "All tests passed" << std::endl;
    return 0;
}
