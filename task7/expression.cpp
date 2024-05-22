#include <iostream>
#include <string>

class Expression {
public:
    virtual Expression* diff(std::string var) const = 0;
    virtual Expression* clone() const = 0;
    virtual std::string toString() const = 0;
    virtual ~Expression() = default;
};

class Binary : public Expression {
protected:
    Expression* left;
    Expression* right;
    virtual std::string sign() const = 0;

    std::string toString() const override {
        return "(" + left->toString() + " " + sign() + " " + right->toString() + ")";
    }

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
    std::string sign() const override {
        return "+";
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

    std::string sign() const override {
        return "-";
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
    std::string sign() const override {
        return "*";
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
    std::string sign() const override {
        return "/";
    }
    ~Div() {}
};

class Val : public Expression {
private:
    int value;
public:
    Val(int v) : value(v) {}
    Expression* diff(std::string var) const override {
        return new Val(0);
    }
    Expression* clone() const override {
        return new Val(value);
    }

    std::string toString() const override {
        return std::to_string(value);
    }

    ~Val() {}
};

class Exponent : public Binary {
public:
    Exponent(Expression* l, Expression* r) : Binary(l, r) {}
    Expression* diff(std::string var) const override {
        // right is a constant
        Expression* one = new Val(1);
        return new Mult(
            new Mult(
                right->clone(),
                new Exponent(left->clone(), new Sub(right->clone(), new Val(1)))
            ),
            left->diff(var)
        );
    }

    Expression* clone() const override {
        return new Exponent(left->clone(), right->clone());
    }
    std::string sign() const override {
        return "^";
    }
    ~Exponent() {}
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
    std::string toString() const override {
        return var_name;
    }
    ~Var() {}
};