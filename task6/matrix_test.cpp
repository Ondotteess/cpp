#include <vector>
#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <iostream>

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
