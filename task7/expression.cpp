#include <iostream>
#include <string>
#include <memory>

class Expression {
public:
    virtual std::shared_ptr<Expression> diff(std::string var) const = 0;
    virtual std::string toString() const = 0;
    virtual ~Expression() = default;
};

class Binary : public Expression {
protected:
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;
    virtual std::string sign() const = 0;

    std::string toString() const override {
        return "(" + left->toString() + " " + sign() + " " + right->toString() + ")";
    }

public:
    Binary(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r) : left(l), right(r) {}
};

class Unary : public Expression {
protected:
    std::shared_ptr<Expression> expr;
public:
    Unary(std::shared_ptr<Expression> e) : expr(e) {}
};

class Add : public Binary {
public:
    Add(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r) : Binary(l, r) {}
    std::shared_ptr<Expression> diff(std::string var) const override {
        return std::make_shared<Add>(left->diff(var), right->diff(var));
    }
    std::string sign() const override {
        return "+";
    }
};

class Sub : public Binary {
public:
    Sub(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r) : Binary(l, r) {}
    std::shared_ptr<Expression> diff(std::string var) const override {
        return std::make_shared<Sub>(left->diff(var), right->diff(var));
    }

    std::string sign() const override {
        return "-";
    }
};

class Mult : public Binary {
public:
    Mult(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r) : Binary(l, r) {}
    std::shared_ptr<Expression> diff(std::string var) const override {
        return std::make_shared<Add>(std::make_shared<Mult>(left->diff(var), right), std::make_shared<Mult>(left, right->diff(var)));
    }
    std::string sign() const override {
        return "*";
    }
};

class Div : public Binary {
public:
    Div(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r) : Binary(l, r) {}
    std::shared_ptr<Expression> diff(std::string var) const override {
        return std::make_shared<Div>(std::make_shared<Sub>(std::make_shared<Mult>(left->diff(var), right), std::make_shared<Mult>(left, right->diff(var))), right);
    }
    std::string sign() const override {
        return "/";
    }
};

class Val : public Expression {
private:
    int value;
public:
    Val(int v) : value(v) {}
    std::shared_ptr<Expression> diff(std::string var) const override {
        return std::make_shared<Val>(0);
    }
    std::string toString() const override {
        return std::to_string(value);
    }
};

class Exponent : public Binary {
public:
    Exponent(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r) : Binary(l, r) {}
    std::shared_ptr<Expression> diff(std::string var) const override {
        // Assume right is a constant
        auto one = std::make_shared<Val>(1);
        return std::make_shared<Mult>(
            std::make_shared<Mult>(
                right,
                std::make_shared<Exponent>(left, std::make_shared<Sub>(right, one))
                ),
            left->diff(var)
            );
    }
    std::string sign() const override {
        return "^";
    }
};

class Var : public Expression {
private:
    std::string var_name;
public:
    Var(std::string name) : var_name(name) {}
    std::shared_ptr<Expression> diff(std::string var) const override {
        if (var_name == var)
            return std::make_shared<Val>(1);
        else
            return std::make_shared<Val>(0);
    } 
    std::string toString() const override {
        return var_name;
    }
};
