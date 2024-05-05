#include <iostream>
#include <string>

class Expression {
public:
    virtual Expression* diff(std::string var) const = 0;
    virtual Expression* clone() const = 0;
    virtual void print() const = 0;
    virtual ~Expression() {}
};

class Binary : public Expression {
protected:
    Expression* left;
    Expression* right;
public:
    Binary(Expression* l, Expression* r) : left(l), right(r) {}
    virtual ~Binary() {
        delete left;
        delete right;
    }
};

class Unary : public Expression {
protected:
    Expression* expr;
public:
    Unary(Expression* e) : expr(e) {}
    virtual ~Unary() {
        delete expr;
    }
};

class Add : public Binary {
public:
    Add(Expression* l, Expression* r) : Binary(l, r) {}
    Expression* diff(std::string var) const override {
        return new Add(left->diff(var), right->diff(var));
    }
    Expression* clone() const override {
        return new Add(left->clone(), right->clone());
    }
    void print() const override {
        left->print();
        std::cout << " + ";
        right->print();
    }
    ~Add() {}
};

class Sub : public Binary {
public:
    Sub(Expression* l, Expression* r) : Binary(l, r) {}
    Expression* diff(std::string var) const override {
        return new Sub(left->diff(var), right->diff(var));
    }
    Expression* clone() const override {
        return new Sub(left->clone(), right->clone());
    }
    void print() const override {
        left->print();
        std::cout << " - ";
        right->print();
    }
    ~Sub() {}
};

class Mult : public Binary {
public:
    Mult(Expression* l, Expression* r) : Binary(l, r) {}
    Expression* diff(std::string var) const override {
        return new Add(new Mult(left->diff(var), right->clone()), new Mult(left->clone(), right->diff(var)));
    }
    Expression* clone() const override {
        return new Mult(left->clone(), right->clone());
    }
    void print() const override {
        left->print();
        std::cout << " * ";
        right->print();
    }
    ~Mult() {}
};

class Div : public Binary {
public:
    Div(Expression* l, Expression* r) : Binary(l, r) {}
    Expression* diff(std::string var) const override {
        return new Div(new Sub(new Mult(left->diff(var), right->clone()), new Mult(left->clone(), right->diff(var))),
            right->clone());
    }
    Expression* clone() const override {
        return new Div(left->clone(), right->clone());
    }
    void print() const override {
        left->print();
        std::cout << " / ";
        right->print();
    }
    ~Div() {}
};

class Exponent : public Binary {
public:
    Exponent(Expression* l, Expression* r) : Binary(l, r) {}
    Expression* diff(std::string var) const override {
        Expression* inner_diff = new Mult(right->clone(), new Exponent(left->clone(), right->clone()->diff(var)));
        Expression* outer_diff = new Mult(new Exponent(left->clone(), right->clone()), left->diff(var));
        return new Mult(inner_diff, outer_diff);
    }
    Expression* clone() const override {
        return new Exponent(left->clone(), right->clone());
    }
    void print() const override {
        left->print();
        std::cout << " ^ ";
        right->print();
    }
    ~Exponent() {}
};

class Val : public Expression {
private:
    double value;
public:
    Val(double v) : value(v) {}
    Expression* diff(std::string var) const override {
        return new Val(0);
    }
    Expression* clone() const override {
        return new Val(value);
    }
    void print() const override {
        std::cout << value;
    }
    ~Val() {}
};

class Var : public Expression {
private:
    std::string var_name;
public:
    Var(std::string name) : var_name(name) {}
    Expression* diff(std::string var) const override {
        if (var_name == var)
            return new Val(1);
        else
            return new Val(0);
    }
    Expression* clone() const override {
        return new Var(var_name);
    }
    void print() const override {
        std::cout << var_name;
    }
    ~Var() {}
};
