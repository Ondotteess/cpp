#include <iostream>
#include <cmath>
#include <limits>

struct Point {
    double x, y;

    Point(double xVal, double yVal) : x(xVal), y(yVal) {}
};

class Line {
public:
    double A, B, C;

    // Line as Ax + By = C
    Line(const Point& p1, const Point& p2) {
        A = p2.y - p1.y;
        B = p1.x - p2.x;
        C = A * p1.x + B * p1.y;
    }

    Line(double a, double b, double c) : A(a), B(b), C(c) {}

    Point intersect(const Line& other) const {
        double determinant = A * other.B - other.A * B;
        if (determinant == 0) {
            return Point(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
        }

        double x = (other.B * C - B * other.C) / determinant;
        double y = (A * other.C - other.A * C) / determinant;

        return Point(x, y);
    }

    Line perpendicularLine(const Point& point) const {
        double D = B * point.x - A * point.y;
        return Line(-A, -B, D);
    }

};

int main() {
    // Test 1
    Point p1(1, 2);
    Point p2(3, 4);
    Line lineFromPoints(p1, p2);
    std::cout << "Line from points: A = " << lineFromPoints.A << ", B = " << lineFromPoints.B << ", C = " << lineFromPoints.C << std::endl;

    // Test 2
    Line lineFromCoefficients(2, -1, 0);
    std::cout << "Line from coefficients: A = " << lineFromCoefficients.A << ", B = " << lineFromCoefficients.B << ", C = " << lineFromCoefficients.C << std::endl;

    // Test 3
    Point p3(5, 6);
    Line lineFromPoint(p3, p1);
    std::cout << "Line from point: A = " << lineFromPoint.A << ", B = " << lineFromPoint.B << ", C = " << lineFromPoint.C << std::endl;

    Line perpendicularLine = lineFromPoint.perpendicularLine(p3);
    std::cout << "Perpendicular line at point " << p3.x << ", " << p3.y << ": A = " << perpendicularLine.A << ", B = " << perpendicularLine.B << ", C = " << perpendicularLine.C << std::endl;

    // Test 4
    Point intersectionPoint = lineFromPoints.intersect(lineFromPoint);
    std::cout << "Intersection point: " << intersectionPoint.x << ", " << intersectionPoint.y << std::endl;

    return 0;
}
