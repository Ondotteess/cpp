#include <iostream>
#include <cassert>
#include "matrix.cpp"


int main() {
    
    // Test: Vector init and double indexing
    {
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

    //Test: addition
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

        Matrix result = m1 + m2;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                std::cout << result[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    //Test: Multiply
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

        Matrix result = m1 * m2;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                std::cout << result[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    //Test: Assigment
    {
        Matrix m1(2);
        m1[0][0] = 1;
        m1[0][1] = 2;
        m1[1][0] = 3;
        m1[1][1] = 4;

        Matrix m2(2);
        m2 = m1;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                std::cout << m2[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}