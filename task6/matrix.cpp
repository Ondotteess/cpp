#include <vector>
#include <stdexcept>

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

    class Wrapper {
    private:
        double* _row;
        size_t _size;
    public:
        Wrapper(double* row, size_t size) : _row(row), _size(size) {}

        double& operator[](size_t col) {
            if (col >= _size) throw std::out_of_range("Index out of range");
            return _row[col];
        }

    };

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

    operator double() const {
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
    Wrapper operator[](size_t index) {
        if (index >= _size) throw std::out_of_range("Index out of range");
        return Wrapper(_data[index], _size);
    }

};
