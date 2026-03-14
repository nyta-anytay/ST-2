// Copyright 2022 UNN-CS
#ifndef INCLUDE_CIRCLE_H_
#define INCLUDE_CIRCLE_H_

#include <cstdint>
#include <cmath>

class Circle {
 private:
    double radius;
    double ference;
    double area;

    static constexpr double PI = 3.14159265358979323846;

 public:
    explicit Circle(double radius);

    void setRadius(double radius);
    void setFerence(double ference);
    void setArea(double area);

    double getRadius() const;
    double getFerence() const;
    double getArea() const;
};

#endif  // INCLUDE_CIRCLE_H_