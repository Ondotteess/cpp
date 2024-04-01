#include <vector>

class Matrix {
private:
    size_t _size;
    double** _data;
public:

    Matrix(size_t size) {
        _size = size;
        _data = new double* [size];
        for (int i = 0; i < size; i++) {
            _data[i] = new double[size];
        }
    }

    Matrix(const Matrix& other) : Matrix(other._size) {
        for (size_t i = 0; i < _size; ++i) {
            for (size_t j = 0; j < _size; ++j) {
                _data[i][j] = other._data[i][j];
            }
        }
    }

    Matrix(const std::vector<double>& vec) {
        _size = vec.size();
        _data = new double* [_size];
        for (size_t i = 0; i < _size; ++i) {
            _data[i] = new double[_size]();
        }

        for (size_t i = 0; i < _size; ++i) {
            _data[i][i] = vec[i];
        }
    }
    
    ~Matrix() {
        for (size_t i = 0; i < _size; ++i) {
            delete[] _data[i];
        }
        delete[] _data;
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

    Matrix operator+(const Matrix& other) const {
        Matrix result(_size);
        for (size_t i = 0; i < _size; ++i) {
            for (size_t j = 0; j < _size; ++j) {
                result._data[i][j] = _data[i][j] + other._data[i][j];
            }
        }
        return result;
    }

    Matrix operator+=(const Matrix& other) const {
        for (size_t i = 0; i < _size; ++i) {
            for (size_t j = 0; j < _size; ++j) {
                _data[i][j] = _data[i][j] + other._data[i][j];
            }
        }
        return *this;
    }

    Matrix operator*(const Matrix other) {
        Matrix result(_size);
        for (int i = 0; i < _size; i++) {
            for (int j = 0; j < _size; j++) {
                result._data[i][j] = 0;
                for (int k = 0; k < _size; k++) {
                    result._data[i][j] += _data[i][k] * other._data[k][j];
                }
            }
        }
        return result;
    }

    Matrix &operator*=(const Matrix other) const {
        Matrix result(_size);
        for (int i = 0; i < _size; i++) {
            for (int j = 0; j < _size; j++) {
                result._data[i][j] = 0;
                for (int k = 0; k < _size; k++) {
                    result._data[i][j] += _data[i][k] * other._data[k][j];
                }
            }
        }
        return result;
    }

    Matrix& operator*=(double scalar) {
        for (size_t i = 0; i < _size; ++i) {
            for (size_t j = 0; j < _size; ++j) {
                _data[i][j] *= scalar;
            }
        }
        return *this;
    }

    Matrix& operator=(Matrix other) {
        if (this != &other) {
            for (size_t i = 0; i < _size; ++i) {
                delete[] _data[i];
            }
            delete[] _data;

            _size = other._size;
            _data = new double* [_size];
            for (size_t i = 0; i < _size; ++i) {
                _data[i] = new double[_size];
                for (size_t j = 0; j < _size; ++j) {
                    _data[i][j] = other._data[i][j];
                }
            }
        }
        return *this;
    }

    bool operator==(const Matrix& other) const {
        if (_size != other._size) {
            return false; 
        }

        for (size_t i = 0; i < _size; ++i) {
            for (size_t j = 0; j < _size; ++j) {
                if (_data[i][j] != other._data[i][j]) {
                    return false; 
                }
            }
        }
        return true; 
    }

    bool operator!=(const Matrix& other) const {
        return !(*this == other);
    }

    double* operator[](size_t index) { 
        return _data[index];
    }
};
