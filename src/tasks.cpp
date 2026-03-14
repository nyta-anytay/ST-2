// Copyright 2022 UNN-CS
#include <cmath>
#include "circle.h"
#include "tasks.h"

double earthAndRope() {
    // Радиус Земли в метрах
    const double earthRadiusM = 6378.1 * 1000.0;

    Circle earth(earthRadiusM);

    // Увеличиваем длину окружности на 1 метр
    double newFerence = earth.getFerence() + 1.0;
    Circle newCircle(0.0);
    newCircle.setFerence(newFerence);

    // Зазор — разность радиусов
    return newCircle.getRadius() - earth.getRadius();
}

PoolCost poolCosts(double poolRadius, double pathWidth,
                   double concreteCostPerSqM, double fenceCostPerM) {
    Circle pool(poolRadius);
    Circle outer(poolRadius + pathWidth);

    // Площадь дорожки = площадь внешнего круга - площадь бассейна
    double pathArea = outer.getArea() - pool.getArea();

    // Длина ограды = длина окружности внешнего круга
    double fenceLength = outer.getFerence();

    PoolCost result;
    result.pathCost  = pathArea * concreteCostPerSqM;
    result.fenceCost = fenceLength * fenceCostPerM;

    return result;
}