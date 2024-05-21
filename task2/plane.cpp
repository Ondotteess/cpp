#include <iostream>
#include <cmath>
#include <limits>

struct Point {
    double x, y;
};

class Line {
private:
    double _A, _B, _C;

public:
    // Line as Ax + By = C
    Line(const Point& p1, const Point& p2) {
        _A = p2.y - p1.y;
        _B = p1.x - p2.x;
        _C = _A * p1.x + _B * p1.y;
    }

    Line(double a, double b, double c) : _A(a), _B(b), _C(c) {}

    Point intersect(const Line& other) const {
        double determinant = _A * other._B - other._A * _B;
        if (determinant == 0) {
            return Point{ std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity() };
        }

        double x = (other._B * _C - _B * other._C) / determinant;
        double y = (_A * other._C - other._A * _C) / determinant;

        return Point{ x, y };
    }

    Line perpendicularLine(const Point& point) const {
        double newA = -_B;
        double newB = _A;
        double newC = newA * point.x + newB * point.y;
        return Line(newA, newB, newC);
    }

    double A() const {
        return _A;
    }

    double B() const {
        return _B;
    }

    double C() const {
        return _C;
    }

};

int main() {
    // Test 1
    Point p1{ 1, 2 };
    Point p2{ 3, 4 };
    Line lineFromPoints(p1, p2);

    std::cout << "Line from points: A = " << lineFromPoints.A() <<
        ", B = " << lineFromPoints.B() <<
        ", C = " << lineFromPoints.C() << std::endl;

    // Test 2
    Line lineFromCoefficients(2, -1, 0);
    std::cout << "Line from coefficients: A = " << lineFromCoefficients.A()
        << ", B = " << lineFromCoefficients.B()
        << ", C = " << lineFromCoefficients.C() << std::endl;

    // Test 3
    Point p3{ 5, 6 };
    Line lineFromPoint(p3, p1);
    std::cout << "Line from point: A = " << lineFromPoint.A()
        << ", B = " << lineFromPoint.B() <<
        ", C = " << lineFromPoint.C() << std::endl;

    Line perpendicularLine = lineFromPoint.perpendicularLine(p3);
    std::cout << "Perpendicular line at point " << p3.x << ", " << p3.y
        << ": A = " << perpendicularLine.A() <<
        ", B = " << perpendicularLine.B() <<
        ", C = " << perpendicularLine.C() << std::endl;

    // Test 4 - intersecting lines
    Point intersectionPoint = lineFromPoints.intersect(lineFromPoint);
    std::cout << "Intersection point of same lines: " << intersectionPoint.x << ", " << intersectionPoint.y << std::endl;

    // Test 5 - parallel lines
    Point a1{ 0, 0 }; Point a2{ 1, 1 };
    Point b1{ -3, -3 }; Point b2{ -2, -2 };

    Line a{ a1, a2 };
    Line b{ b1, b2 };
    Point intersectionParallel = b.intersect(a);
    std::cout << "Intersection point of parallel lines: " << intersectionParallel.x << ", " << intersectionParallel.y << std::endl;

    return 0;
}
