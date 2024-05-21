#include <iostream>

template<typename T>
class ScopedPointerDeep {
private:
    T* ptr;

public:
    ScopedPointerDeep(T* p = nullptr) : ptr(p) {}

    ~ScopedPointerDeep() {
        delete ptr;
    }

    // copy
    ScopedPointerDeep(const ScopedPointerDeep& other) : ptr(nullptr) {
        std::cout << "copy ctr called!\n";
        if (other.ptr) {
            ptr = new T(*other.ptr);
        }
    }

    // move
    ScopedPointerDeep(ScopedPointerDeep&& other) : ptr(other.ptr) {
        std::cout << "move ctr called!\n";
        other.ptr = nullptr;
    }

    // copy-and-swap 
    ScopedPointerDeep& operator=(ScopedPointerDeep other) {
        std::cout << "copy assigmnet oper!\n";
        swap(*this, other);
        return *this;
    }

    // move
    ScopedPointerDeep& operator=(ScopedPointerDeep&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // redefine swap
    void swap(ScopedPointerDeep& first, ScopedPointerDeep& second) noexcept {
        std::swap(first.ptr, second.ptr);
    }

    T* operator->() const {
        return ptr;
    }

    T& operator*() const {
        return *ptr;
    }
};


template<typename T>
class ScopedPointerTransfer {
private:
    T* ptr;

public:
    ScopedPointerTransfer(T* p = nullptr) : ptr(p) {}

    ~ScopedPointerTransfer() {
        delete ptr;
    }

    ScopedPointerTransfer(ScopedPointerTransfer&& other) : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    //deleted auto copy ctrs
    ScopedPointerTransfer(const ScopedPointerTransfer&) = delete;

    ScopedPointerTransfer& operator=(const ScopedPointerTransfer&) = delete;


    ScopedPointerTransfer& operator=(ScopedPointerTransfer&& other) {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T* operator->() const {
        return ptr;
    }

    T& operator*() const {
        return *ptr;
    }
};
