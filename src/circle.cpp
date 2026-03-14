// Copyright 2022 UNN-CS
#include <cmath>
#include "circle.h"

Circle::Circle(double radius) {
    this->radius   = radius;
    this->ference  = 2.0 * PI * radius;
    this->area     = PI * radius * radius;
}

void Circle::setRadius(double radius) {
    this->radius  = radius;
    this->ference = 2.0 * PI * radius;
    this->area    = PI * radius * radius;
}

void Circle::setFerence(double ference) {
    this->ference = ference;
    this->radius  = ference / (2.0 * PI);
    this->area    = PI * this->radius * this->radius;
}

void Circle::setArea(double area) {
    this->area    = area;
    this->radius  = std::sqrt(area / PI);
    this->ference = 2.0 * PI * this->radius;
}

double Circle::getRadius() const {
    return radius;
}

double Circle::getFerence() const {
    return ference;
}

double Circle::getArea() const {
    return area;
}