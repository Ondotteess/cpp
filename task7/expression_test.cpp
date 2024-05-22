#include <iostream>
#include <string>
#include <memory>
#include "expression.cpp"


int main() {
    // Test case 1: e = x + 10 * y
    std::shared_ptr<Expression> e = std::make_shared<Add>(std::make_shared<Var>("x"), std::make_shared<Mult>(std::make_shared<Val>(10), std::make_shared<Var>("y")));
    std::shared_ptr<Expression> res1 = e->diff("x");
    std::shared_ptr<Expression> res2 = e->diff("y");

    std::cout << "Test case 1:" << std::endl;
    std::cout << "e = " << e->toString() << std::endl;
    std::cout << "res1 = " << res1->toString() << std::endl;
    std::cout << "res2 = " << res2->toString() << std::endl;

    // Test case 2: f = (x * x) - (2 * x) + 1
    std::shared_ptr<Expression> f = std::make_shared<Sub>(std::make_shared<Sub>(std::make_shared<Mult>(std::make_shared<Var>("x"), std::make_shared<Var>("x")), std::make_shared<Mult>(std::make_shared<Val>(2), std::make_shared<Var>("x"))), std::make_shared<Val>(1));
    std::shared_ptr<Expression> res3 = f->diff("x");

    std::cout << "Test case 2:" << std::endl;
    std::cout << "f = " << f->toString() << std::endl;
    std::cout << "df/dx = " << res3->toString() << std::endl;

    // Test case 3: g = (x^2) + (y^3)
    std::shared_ptr<Expression> g = std::make_shared<Add>(std::make_shared<Exponent>(std::make_shared<Var>("x"), std::make_shared<Val>(2)), std::make_shared<Exponent>(std::make_shared<Var>("y"), std::make_shared<Val>(3)));
    std::shared_ptr<Expression> res4 = g->diff("x");
    std::shared_ptr<Expression> res5 = g->diff("y");

    std::cout << "Test case 3:" << std::endl;
    std::cout << "g = " << g->toString() << std::endl;
    std::cout << "dg/dx = " << res4->toString() << std::endl;
    std::cout << "dg/dy = " << res5->toString() << std::endl;

}
