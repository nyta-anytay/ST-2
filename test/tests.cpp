// Copyright 2025 UNN-CS Team

#include <gtest/gtest.h>
#include <cmath>
#include "circle.h"
#include "tasks.h"

static constexpr double PI      = 3.14159265358979323846;
static constexpr double EPS     = 1e-9;
static constexpr double EPS_LOW = 1e-5;

// ──────────────────────────────────────────────
// Тесты класса Circle
// ──────────────────────────────────────────────

// 1. Конструктор с радиусом 0
TEST(CircleConstructor, ZeroRadius) {
    Circle c(0.0);
    EXPECT_NEAR(c.getRadius(),  0.0, EPS);
    EXPECT_NEAR(c.getFerence(), 0.0, EPS);
    EXPECT_NEAR(c.getArea(),    0.0, EPS);
}

// 2. Конструктор с радиусом 1
TEST(CircleConstructor, UnitRadius) {
    Circle c(1.0);
    EXPECT_NEAR(c.getRadius(),  1.0,        EPS);
    EXPECT_NEAR(c.getFerence(), 2.0 * PI,   EPS);
    EXPECT_NEAR(c.getArea(),    PI,          EPS);
}

// 3. Конструктор с произвольным радиусом
TEST(CircleConstructor, ArbitraryRadius) {
    Circle c(5.0);
    EXPECT_NEAR(c.getRadius(),  5.0,         EPS);
    EXPECT_NEAR(c.getFerence(), 2.0 * PI * 5.0, EPS);
    EXPECT_NEAR(c.getArea(),    PI * 25.0,   EPS);
}

// 4. setRadius пересчитывает окружность и площадь
TEST(CircleSetRadius, RecalcFerenceAndArea) {
    Circle c(1.0);
    c.setRadius(3.0);
    EXPECT_NEAR(c.getRadius(),  3.0,          EPS);
    EXPECT_NEAR(c.getFerence(), 2.0 * PI * 3.0, EPS);
    EXPECT_NEAR(c.getArea(),    PI * 9.0,     EPS);
}

// 5. setRadius(0) обнуляет все поля
TEST(CircleSetRadius, ZeroRecalc) {
    Circle c(10.0);
    c.setRadius(0.0);
    EXPECT_NEAR(c.getRadius(),  0.0, EPS);
    EXPECT_NEAR(c.getFerence(), 0.0, EPS);
    EXPECT_NEAR(c.getArea(),    0.0, EPS);
}

// 6. setFerence пересчитывает радиус и площадь
TEST(CircleSetFerence, RecalcRadiusAndArea) {
    Circle c(0.0);
    double f = 2.0 * PI * 4.0;   // ference для r = 4
    c.setFerence(f);
    EXPECT_NEAR(c.getRadius(), 4.0,       EPS);
    EXPECT_NEAR(c.getArea(),   PI * 16.0, EPS);
}

// 7. setFerence(0) обнуляет радиус и площадь
TEST(CircleSetFerence, ZeroFerence) {
    Circle c(5.0);
    c.setFerence(0.0);
    EXPECT_NEAR(c.getRadius(), 0.0, EPS);
    EXPECT_NEAR(c.getArea(),   0.0, EPS);
}

// 8. setArea пересчитывает радиус и окружность
TEST(CircleSetArea, RecalcRadiusAndFerence) {
    Circle c(0.0);
    double a = PI * 9.0;    // площадь для r = 3
    c.setArea(a);
    EXPECT_NEAR(c.getRadius(),  3.0,          EPS);
    EXPECT_NEAR(c.getFerence(), 2.0 * PI * 3.0, EPS);
}

// 9. setArea(0) обнуляет радиус и окружность
TEST(CircleSetArea, ZeroArea) {
    Circle c(7.0);
    c.setArea(0.0);
    EXPECT_NEAR(c.getRadius(),  0.0, EPS);
    EXPECT_NEAR(c.getFerence(), 0.0, EPS);
}

// 10. Цепочка: setRadius → setFerence → вернуться к тому же радиусу
TEST(CircleChain, RadiusViaFerence) {
    Circle c(6.0);
    double f = c.getFerence();
    c.setFerence(f);
    EXPECT_NEAR(c.getRadius(), 6.0, EPS);
}

// 11. Цепочка: setRadius → setArea → вернуться к тому же радиусу
TEST(CircleChain, RadiusViaArea) {
    Circle c(6.0);
    double a = c.getArea();
    c.setArea(a);
    EXPECT_NEAR(c.getRadius(), 6.0, EPS);
}

// 12. Большой радиус (радиус Земли в км)
TEST(CircleEdge, LargeRadius) {
    double r = 6378.1;
    Circle c(r);
    EXPECT_NEAR(c.getRadius(),  r,              EPS);
    EXPECT_NEAR(c.getFerence(), 2.0 * PI * r,   EPS);
    EXPECT_NEAR(c.getArea(),    PI * r * r,      EPS);
}

// 13. Два объекта не влияют друг на друга
TEST(CircleIndependence, TwoObjects) {
    Circle c1(2.0);
    Circle c2(5.0);
    c1.setRadius(10.0);
    EXPECT_NEAR(c2.getRadius(), 5.0, EPS);
}

// 14. getRadius возвращает именно установленное значение
TEST(CircleGetters, GetRadiusCorrect) {
    Circle c(42.0);
    EXPECT_DOUBLE_EQ(c.getRadius(), 42.0);
}

// 15. Соотношение: ference = 2*PI*radius для любого r
TEST(CircleConsistency, FerenceEquality) {
    for (double r : {0.1, 1.0, 10.0, 100.0}) {
        Circle c(r);
        EXPECT_NEAR(c.getFerence(), 2.0 * PI * r, EPS);
    }
}

// ──────────────────────────────────────────────
// Тесты задачи "Земля и верёвка"
// ──────────────────────────────────────────────

// 16. Зазор должен быть положительным
TEST(EarthAndRope, GapIsPositive) {
    double gap = earthAndRope();
    EXPECT_GT(gap, 0.0);
}

// 17. Зазор равен 1 / (2*PI) ≈ 0.159155 м (аналитическое решение)
TEST(EarthAndRope, GapValue) {
    double expected = 1.0 / (2.0 * PI);
    EXPECT_NEAR(earthAndRope(), expected, EPS_LOW);
}

// 18. Зазор не зависит от радиуса Земли (проверка через Circle вручную)
TEST(EarthAndRope, GapIndependentOfRadius) {
    // Для любого начального радиуса добавление 1 м к длине
    // даёт зазор 1/(2*PI)
    double expected = 1.0 / (2.0 * PI);

    for (double r : {100.0, 1000.0, 6378100.0}) {
        Circle earth(r);
        Circle bigger(0.0);
        bigger.setFerence(earth.getFerence() + 1.0);
        EXPECT_NEAR(bigger.getRadius() - earth.getRadius(), expected, EPS_LOW);
    }
}

// ──────────────────────────────────────────────
// Тесты задачи "Бассейн"
// ──────────────────────────────────────────────

// 19. Стоимость дорожки: площадь кольца * 1000
TEST(Pool, PathCost) {
    PoolCost pc = poolCosts(3.0, 1.0, 1000.0, 2000.0);
    double innerArea = PI * 9.0;
    double outerArea = PI * 16.0;
    double expected  = (outerArea - innerArea) * 1000.0;
    EXPECT_NEAR(pc.pathCost, expected, EPS_LOW);
}

// 20. Стоимость ограды: длина окружности внешнего круга * 2000
TEST(Pool, FenceCost) {
    PoolCost pc = poolCosts(3.0, 1.0, 1000.0, 2000.0);
    double outerFerence = 2.0 * PI * 4.0;
    double expected     = outerFerence * 2000.0;
    EXPECT_NEAR(pc.fenceCost, expected, EPS_LOW);
}

// 21. При нулевой ширине дорожки стоимость бетона = 0
TEST(Pool, ZeroPathWidth) {
    PoolCost pc = poolCosts(3.0, 0.0, 1000.0, 2000.0);
    EXPECT_NEAR(pc.pathCost, 0.0, EPS_LOW);
}

// 22. При нулевой ширине дорожки ограда идёт по краю бассейна
TEST(Pool, ZeroPathWidthFence) {
    PoolCost pc = poolCosts(3.0, 0.0, 1000.0, 2000.0);
    double expected = 2.0 * PI * 3.0 * 2000.0;
    EXPECT_NEAR(pc.fenceCost, expected, EPS_LOW);
}

// 23. Масштабирование: удвоение цен удваивает стоимости
TEST(Pool, PriceScaling) {
    PoolCost pc1 = poolCosts(3.0, 1.0, 1000.0, 2000.0);
    PoolCost pc2 = poolCosts(3.0, 1.0, 2000.0, 4000.0);
    EXPECT_NEAR(pc2.pathCost,  pc1.pathCost  * 2.0, EPS_LOW);
    EXPECT_NEAR(pc2.fenceCost, pc1.fenceCost * 2.0, EPS_LOW);
}

