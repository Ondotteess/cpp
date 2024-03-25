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

    ScopedPointerDeep(const ScopedPointerDeep& other) : ptr(nullptr) {
        if (other.ptr) {
            ptr = new T(*other.ptr);
        }
    }

    ScopedPointerDeep& operator=(const ScopedPointerDeep& other) {
        if (this != &other) {
            delete ptr;
            ptr = nullptr;
            if (other.ptr) {
                ptr = new T(*other.ptr);
            }
        }
        return *this;
    }

    ScopedPointerDeep(ScopedPointerDeep&& other): ptr(other.ptr) {
        other.ptr = nullptr;
    }

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

    ScopedPointerTransfer(const ScopedPointerTransfer& other) = delete;

    ScopedPointerTransfer(ScopedPointerTransfer&& other) : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    ScopedPointerTransfer& operator=(const ScopedPointerTransfer& other) = delete;

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
