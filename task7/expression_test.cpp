#include <iostream>
#include <string>
#include "expression.cpp"

int main() {
    // Test case 1: e = x + 10 * y
    Expression* e = new Add(new Var("x"), new Mult(new Val(10), new Var("y")));
    Expression* res1 = e->diff("x");
    Expression* res2 = e->diff("y");

    std::cout << "Test case 1:" << std::endl;
    std::cout << "e = ";
    e->print();
    std::cout << std::endl;

    std::cout << "res1 = ";
    res1->print();
    std::cout << std::endl;

    std::cout << "res2 = ";
    res2->print();
    std::cout << std::endl << std::endl;

    delete e;
    delete res1;
    delete res2;

    // Test case 2: f = (x * x) - (2 * x) + 1
    Expression* f = new Sub(new Sub(new Mult(new Var("x"), new Var("x")), new Mult(new Val(2), new Var("x"))), new Val(1));
    Expression* res3 = f->diff("x");

    std::cout << "Test case 2:" << std::endl;
    std::cout << "f = ";
    f->print();
    std::cout << std::endl;

    std::cout << "f' = ";
    res3->print();
    std::cout << std::endl << std::endl;

    delete f;
    delete res3;

    // Test case 3: g = (x^2) + (y^3)
    Expression* g = new Add(new Exponent(new Var("x"), new Val(2)), new Exponent(new Var("y"), new Val(3)));
    Expression* res4 = g->diff("x");
    Expression* res5 = g->diff("y");

    std::cout << "Test case 3:" << std::endl;
    std::cout << "g = ";
    g->print();
    std::cout << std::endl;

    std::cout << "dg/dx = ";
    res4->print();
    std::cout << std::endl;

    std::cout << "dg/dy = ";
    res5->print();
    std::cout << std::endl << std::endl;

    delete g;
    delete res4;
    delete res5;

    return 0;
}
