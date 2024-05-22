#include <iostream>
#include <stdexcept>

template <typename Derived, int Limit>
class LimitMixin {
private:
    static int instanceCount;

protected:
    LimitMixin() {
        if (instanceCount >= Limit) {
            throw std::runtime_error("Instance limit exceeded");
        }
        instanceCount++;
    }

    LimitMixin(const LimitMixin&) {
        if (instanceCount >= Limit) {
            throw std::runtime_error("Instance limit exceeded");
        }
        instanceCount++;
    }

public:
    ~LimitMixin() {
        instanceCount--;
    }
};

template <typename Derived, int Limit>
int LimitMixin<Derived, Limit>::instanceCount = 0;

class Test : public LimitMixin<Test, 3> {
public:
    Test() {
        std::cout << "Test instance created." << std::endl;
    }

    Test(const Test& other) : LimitMixin(other) {
        std::cout << "Test instance copied." << std::endl;
    }
};

class Test5 : public LimitMixin<Test5, 5> {
public:
    Test5() {
        std::cout << "Test5 instance created." << std::endl;
    }

    Test5(const Test5& other) : LimitMixin(other) {
        std::cout << "Test5 instance copied." << std::endl;
    }
};

int main() {
    try {
        Test obj1;
        Test obj2;
        Test obj3;
        Test obj4;
    }
    catch (const std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
        std::cout << "default ctr\n\n";
    }


    try {
        Test obj1;
        Test obj2 = obj1;
        Test obj3 = obj1;
        Test obj4 = obj1;
    }
    catch (const std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
        std::cout << "copy ctor\n";
    }


    try {
        Test5 a;
        Test5 b;
        Test5 c;
        Test5 d;
    }
    catch (const std::exception& e) {
        std::cout << "You shouldn't see this\n";
    }
    return 0;
}
