#include <vector>
#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <iostream>

using namespace std;

class Matrix {
private:
    size_t _size;
    double** _data;

    // allocator
    void allocateData(size_t size) {
        _data = new double* [size];
        for (size_t i = 0; i < size; ++i) {
            _data[i] = new double[size]();
        }
    }

    void deallocateData() {
        if (_data) {
            for (size_t i = 0; i < _size; ++i) {
                delete[] _data[i];
            }
            delete[] _data;
            _data = nullptr;
        }
    }

public:

    Matrix(size_t size) : _size(size) {
        allocateData(size);
    }

    // copy
    Matrix(const Matrix& other) : _size(other._size) {
        allocateData(_size);
        for (size_t i = 0; i < _size; ++i) {
            for (size_t j = 0; j < _size; ++j) {
                _data[i][j] = other._data[i][j];
            }
        }
    }

    // move
    Matrix(Matrix&& other) noexcept : _size(other._size), _data(other._data) {
        other._size = 0;
        other._data = nullptr;
    }


    Matrix(const std::vector<double>& vec) {
        _size = vec.size();
        allocateData(_size);
        for (size_t i = 0; i < _size; ++i) {
            _data[i][i] = vec[i];
        }
    }

    // Destructor
    ~Matrix() {
        deallocateData();
    }

    // copy assignment 
    Matrix& operator=(Matrix other) {
        swap(*this, other);
        return *this;
    }

    // move assignment 
    Matrix& operator=(Matrix&& other) noexcept {
        if (this != &other) {
            deallocateData();
            _size = other._size;
            _data = other._data;
            other._size = 0;
            other._data = nullptr;
        }
        return *this;
    }

    // swap redefine
    void swap(Matrix& first, Matrix& second) noexcept {
        using std::swap;
        swap(first._size, second._size);
        swap(first._data, second._data);
    }

    explicit operator double() const {
        double sum = 0.0;
        for (size_t i = 0; i < _size; ++i) {
            for (size_t j = 0; j < _size; ++j) {
                sum += _data[i][j];
            }
        }
        return sum;
    }

    // addition op
    Matrix operator+(const Matrix& other) const {
        if (_size != other._size) throw std::invalid_argument("Matrix sizes must match");
        Matrix result(_size);
        for (size_t i = 0; i < _size; ++i) {
            for (size_t j = 0; j < _size; ++j) {
                result._data[i][j] = _data[i][j] + other._data[i][j];
            }
        }
        return result;
    }

    // addition-assignment op
    Matrix& operator+=(const Matrix& other) {
        if (_size != other._size) throw std::invalid_argument("Matrix sizes must match");
        for (size_t i = 0; i < _size; ++i) {
            for (size_t j = 0; j < _size; ++j) {
                _data[i][j] += other._data[i][j];
            }
        }
        return *this;
    }

    // multiplication operator
    Matrix operator*(const Matrix& other) const {
        if (_size != other._size) throw std::invalid_argument("Matrix sizes must match");
        Matrix result(_size);
        for (size_t i = 0; i < _size; ++i) {
            for (size_t j = 0; j < _size; ++j) {
                result._data[i][j] = 0;
                for (size_t k = 0; k < _size; ++k) {
                    result._data[i][j] += _data[i][k] * other._data[k][j];
                }
            }
        }
        return result;
    }

    // multiplication-assignment operator
    Matrix& operator*=(const Matrix& other) {
        if (_size != other._size) throw std::invalid_argument("Matrix sizes must match");
        Matrix result(_size);
        for (size_t i = 0; i < _size; ++i) {
            for (size_t j = 0; j < _size; ++j) {
                result._data[i][j] = 0;
                for (size_t k = 0; k < _size; ++k) {
                    result._data[i][j] += _data[i][k] * other._data[k][j];
                }
            }
        }
        swap(result, *this);
        return *this;
    }

    Matrix& operator*=(double scalar) {
        for (size_t i = 0; i < _size; ++i) {
            for (size_t j = 0; j < _size; ++j) {
                _data[i][j] *= scalar;
            }
        }
        return *this;
    }

    bool operator==(const Matrix& other) const {
        if (_size != other._size) return false;
        for (size_t i = 0; i < _size; ++i) {
            for (size_t j = 0; j < _size; ++j) {
                if (_data[i][j] != other._data[i][j]) return false;
            }
        }
        return true;
    }

    bool operator!=(const Matrix& other) const {
        return !(*this == other);
    }

    // bounds checking
    double* operator[](size_t index) {
        if (index >= _size) throw std::out_of_range("Index out of range");
        return _data[index];
    }

    const double* operator[](size_t index) const {
        if (index >= _size) throw std::out_of_range("Index out of range");
        return _data[index];
    }

};

// Test functions
void testBoundsChecking() {
    Matrix m(2);
    try {
        m[2][0] = 1.0; // Should throw
    }
    catch (const std::out_of_range& e) {
        std::cout << "Bounds check passed: " << e.what() << std::endl;
    }
}

void testOperators() {
    Matrix m1(2);
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[1][0] = 3;
    m1[1][1] = 4;

    Matrix m2(2);
    m2[0][0] = 5;
    m2[0][1] = 6;
    m2[1][0] = 7;
    m2[1][1] = 8;

    Matrix result = m1 + m2;
    std::cout << "Addition result:" << std::endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            std::cout << result[i][j] << " ";
        }
        std::cout << std::endl;
    }

    m1 += m2;
    std::cout << "Addition-assignment result:" << std::endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            std::cout << m1[i][j] << " ";
        }
        std::cout << std::endl;
    }

    Matrix result2 = m1 * m2;
    std::cout << "Multiplication result:" << std::endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            std::cout << result2[i][j] << " ";
        }
        std::cout << std::endl;
    }

    m1 *= m2;
    std::cout << "Multiplication-assignment result:" << std::endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            std::cout << m1[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void testMoveSemantics() {
    Matrix m1(2);
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[1][0] = 3;
    m1[1][1] = 4;

    Matrix m2 = std::move(m1);
    std::cout << "Move constructor result:" << std::endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            std::cout << m2[i][j] << " ";
        }
        std::cout << std::endl;
    }

    Matrix m3(2);
    m3 = m2;
    std::cout << "Move assignment operator result:" << std::endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            std::cout << m3[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


int main() {
    // Test: Vector init and double indexing
    {
        std::cout << "Diagonal init" << std::endl;
        std::vector<double> vec = { 1, 2, 3, 4 };
        Matrix m(vec);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                std::cout << m[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    // Test: addition
    {
        Matrix m1(2);
        m1[0][0] = 1;
        m1[0][1] = 2;
        m1[1][0] = 3;
        m1[1][1] = 4;

        Matrix m2(2);
        m2[0][0] = 5;
        m2[0][1] = 6;
        m2[1][0] = 7;
        m2[1][1] = 8;

        std::cout << "Test mat addition" << std::endl;
        Matrix result = m1 + m2;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                std::cout << result[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    // Test: Multiply
    {
        Matrix m1(2);
        m1[0][0] = 1;
        m1[0][1] = 2;
        m1[1][0] = 3;
        m1[1][1] = 4;

        Matrix m2(2);
        m2[0][0] = 5;
        m2[0][1] = 6;
        m2[1][0] = 7;
        m2[1][1] = 8;

        std::cout << "Test mult mat" << std::endl;
        Matrix result = m1 * m2;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                std::cout << result[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    // Test: Assignment
    {
        Matrix m1(2);
        m1[0][0] = 1;
        m1[0][1] = 2;
        m1[1][0] = 3;
        m1[1][1] = 4;

        Matrix m2(2);
        m2 = m1;
        std::cout << "Mat assignment oper" << std::endl;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                std::cout << m2[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    testBoundsChecking();
    testOperators();
    testMoveSemantics();

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
