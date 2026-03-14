// Copyright 2022 UNN-CS
#ifndef INCLUDE_TASKS_H_
#define INCLUDE_TASKS_H_

// Задача "Земля и верёвка"
// Возвращает величину зазора в метрах
double earthAndRope();

struct PoolCost {
    double pathCost;
    double fenceCost;
};

// Задача "Бассейн"
// Возвращает структуру со стоимостью дорожки и ограды
PoolCost poolCosts(double poolRadius, double pathWidth,
                   double concreteCostPerSqM, double fenceCostPerM);

#endif  // INCLUDE_TASKS_H_

