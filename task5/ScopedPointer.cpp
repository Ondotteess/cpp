#include <iostream>

template<typename T>
class ScopedPointerDeep {
private:
    T* ptr;

public:
    ScopedPointerDeep(T* p) : ptr(p) {}

    ~ScopedPointerDeep() {
        delete ptr;
    }

    //copy
    ScopedPointerDeep(const ScopedPointerDeep& other) : ptr(nullptr) {
        if (other.ptr) {
            ptr = new T(*other.ptr);
        }
    }

    //move
    ScopedPointerDeep(ScopedPointerDeep&& other): ptr(other.ptr) {
        other.ptr = nullptr;
    }

    //copy
    ScopedPointerDeep& operator=(const ScopedPointerDeep& other) {
        if (this != &other) {
            delete ptr;
            if (other.ptr) {
                ptr = new T(*other.ptr);
            }
        }
        return *this;
    }

    //move
    ScopedPointerDeep& operator=(ScopedPointerDeep&& other) {
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
