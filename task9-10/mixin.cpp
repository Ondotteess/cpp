#include <iostream>

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
        std::cout << "instance created." << std::endl;
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
    }

    return 0;
}
