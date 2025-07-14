#pragma once
#include <math.h>
#include <stdint.h>

class GVector {
   public:
    float x = 0;
    float y = 0;

    // ================ CONSTR ================

    constexpr GVector() = default;
    constexpr GVector(float x, float y) : x(x), y(y) {}

    // ================ FABRIC ================

    // создать из угла (единичный)
    static GVector fromAngle(float rad) {
        return GVector(cosf(rad), sinf(rad));
    }

    // создать из полярных координат
    static GVector fromPolar(float rad, float mag) {
        return fromAngle(rad).mul(mag);
    }

    // создать нулевой
    static GVector fromZero() {
        return GVector(0, 0);
    }

    // ================ STATIC ================

    static constexpr float pi = 3.14159265358979323846f;

    // из радиан в градусы
    static constexpr float toDeg(float rad) { return rad * 180.f / pi; }

    // из градусов в радианы
    static constexpr float toRad(float deg) { return deg * pi / 180.f; }

    // кратчайший угол поворота из from в to (радианы)
    static float shortAngle(float from, float to) {
        float d = to - from;
        while (d < -pi) d += 2 * pi;
        while (d > pi) d -= 2 * pi;
        return d;
    }

    // кратчайший угол поворота из from в to (градусы)
    static int shortAngleDeg(int from, int to) {
        int d = to - from;
        while (d < -180) d += 360;
        while (d > 180) d -= 360;
        return d;
    }

    // угол между
    static float angleBetween(const GVector& a, const GVector& b) {
        float mags = a.mag() * b.mag();
        if (mags == 0) return 0;

        float cos = a.dot(b) / mags;
        return acosf((cos < -1) ? -1 : (cos > 1 ? 1 : cos));
    }

    // расстояние между в квадрате
    static float distSq(const GVector& a, const GVector& b) {
        float dx = b.x - a.x;
        float dy = b.y - a.y;
        return dx * dx + dy * dy;
    }

    // расстояние между
    static float dist(const GVector& a, const GVector& b) {
        return sqrtf(distSq(a, b));
    }

    // скалярное произведение (== 0 - перпендикулярны, > 0 в одну сторону, < 0 в противоположные)
    static float dot(const GVector& a, const GVector& b) {
        return a.x * b.x + a.y * b.y;
    }

    // векторное произведение (< 0 — по часовой, > 0 против часовой)
    static float cross(const GVector& a, const GVector& b) {
        return a.x * b.y - a.y * b.x;
    }

    // векторная проекция на другой вектор
    static GVector project(const GVector& a, const GVector& b) {
        float bmag = b.magSq();
        return (bmag != 0) ? (b * (a.dot(b) / bmag)) : GVector(0, 0);
    }

    // проекция точки P на линию AB
    static GVector projectPoint(const GVector& A, const GVector& B, const GVector& P) {
        return A + project(P - A, B - A);
    }

    // расстояние (перпендикуляр) от точки P до линии AB
    static float distToLine(const GVector& A, const GVector& B, const GVector& P) {
        return dist(P, projectPoint(A, B, P));
    }

    // сложить
    static GVector add(const GVector& v1, const GVector& v2) {
        return GVector(v1.x + v2.x, v1.y + v2.y);
    }
    static GVector add(const GVector& v1, float s) {
        return GVector(v1.x + s, v1.y + s);
    }

    // вычесть
    static GVector sub(const GVector& v1, const GVector& v2) {
        return GVector(v1.x - v2.x, v1.y - v2.y);
    }
    static GVector sub(const GVector& v1, float s) {
        return GVector(v1.x - s, v1.y - s);
    }

    // умножить
    static GVector mul(const GVector& v1, const GVector& v2) {
        return GVector(v1.x * v2.x, v1.y * v2.y);
    }
    static GVector mul(const GVector& v1, float s) {
        return GVector(v1.x * s, v1.y * s);
    }

    // разделить
    static GVector div(const GVector& v1, const GVector& v2) {
        return GVector(v2.x ? (v1.x / v2.x) : 0, v2.y ? (v1.y / v2.y) : 0);
    }
    static GVector div(const GVector& v1, float s) {
        return s ? GVector(v1.x / s, v1.y / s) : GVector(0, 0);
    }

    // ================ ADD ================
    GVector& add(float v) {
        return set(x + v, y + v);
    }
    GVector& operator+=(float v) {
        return add(v);
    }
    GVector operator+(float v) const {
        return add(*this, v);
    }

    GVector& add(const GVector& v) {
        return set(x + v.x, y + v.y);
    }
    GVector& operator+=(const GVector& v) {
        return add(v);
    }
    GVector operator+(const GVector& v) const {
        return add(*this, v);
    }

    // ================ SUB ================
    GVector& sub(float v) {
        return set(x - v, y - v);
    }
    GVector& operator-=(float v) {
        return sub(v);
    }
    GVector operator-(float v) const {
        return sub(*this, v);
    }

    GVector& sub(const GVector& v) {
        return set(x - v.x, y - v.y);
    }
    GVector& operator-=(const GVector& v) {
        return sub(v);
    }
    GVector operator-(const GVector& v) const {
        return sub(*this, v);
    }

    GVector operator-() const {
        return GVector(-x, -y);
    }

    // ================ MUL ================
    GVector& mul(float v) {
        return set(x * v, y * v);
    }
    GVector& operator*=(float v) {
        return mul(v);
    }
    GVector operator*(float v) const {
        return mul(*this, v);
    }

    GVector& mul(const GVector& v) {
        return set(x * v.x, y * v.y);
    }
    GVector& operator*=(const GVector& v) {
        return mul(v);
    }
    GVector operator*(const GVector& v) const {
        return mul(*this, v);
    }

    // ================ DIV ================
    GVector& div(float v) {
        return v ? set(x / v, y / v) : set(0, 0);
    }
    GVector& operator/=(float v) {
        return div(v);
    }
    GVector operator/(float v) const {
        return div(*this, v);
    }

    GVector& div(const GVector& v) {
        return set(v.x ? (x / v.x) : 0, v.y ? (y / v.y) : 0);
    }
    GVector& operator/=(const GVector& v) {
        return div(v);
    }
    GVector operator/(const GVector& v) const {
        return div(*this, v);
    }

    // ================ COMPARE ================

    // проверка равенства с учетом epsilon
    bool equals(const GVector& v, float tolerance = 1e-6f) const {
        return (fabs(x - v.x) < tolerance) && (fabs(y - v.y) < tolerance);
    }

    bool operator==(const GVector& v) const {
        return equals(v);
    }

    bool operator!=(const GVector& v) const {
        return !equals(v);
    }

    // проверка на нулевую длину
    operator bool() const {
        return isZero();
    }

    // ================ GET ================

    // создать копию
    constexpr GVector copy() const {
        return GVector(x, y);
    }

    // длина в квадрате
    constexpr float magSq() const {
        return x * x + y * y;
    }

    // длина
    float mag() const {
        return sqrtf(magSq());
    }

    // скалярное произведение (== 0 - перпендикулярны, > 0 в одну сторону, < 0 в противоположные)
    float dot(const GVector& v) const {
        return dot(*this, v);
    }

    // векторное произведение (поворот к v: < 0 — по часовой, > 0 против часовой)
    float cross(const GVector& v) const {
        return cross(*this, v);
    }

    // сравнение по направлению с угловой толерантностью
    bool isParallelTo(const GVector& v, float tolerance = 1e-6f) const {
        return fabs(cross(v)) < tolerance;
    }

    // угол между
    float angleBetween(const GVector& v) const {
        return angleBetween(*this, v);
    }

    // нормаль
    GVector normal() const {
        return GVector(-y, x).normalize();
    }

    // нормализованная копия
    GVector normalized() const {
        return *this / mag();
    }

    // длина проекции на вектор
    float projectMag(const GVector& v) const {
        float mag = v.mag();
        return (mag != 0) ? (dot(v) / mag) : 0;
    }

    // векторная проекция на другой вектор
    GVector project(const GVector& v) const {
        return project(*this, v);
    }

    // проекция точки на линию AB
    GVector projectPoint(const GVector& A, const GVector& B) const {
        return projectPoint(A, B, *this);
    }

    // расстояние (перпендикуляр) до линии AB
    float distToLine(const GVector& A, const GVector& B) const {
        return distToLine(A, B, *this);
    }

    // расстояние в квадрате
    float distSq(const GVector& v) const {
        return distSq(*this, v);
    }

    // расстояние до
    float dist(const GVector& v) const {
        return dist(*this, v);
    }

    // текущий угол между вектором и осью X
    float heading() const {
        return atan2f(y, x);
    }

    // текущий угол между вектором и осью X
    float headingDeg() const {
        return toDeg(heading());
    }

    // проверка на ноль или epsilon
    bool isZero(float epsilon = 1e-6f) const {
        return fabs(x) < epsilon && fabs(y) < epsilon;
    }

    // ================ MODIFY ================

    // установить
    inline GVector& set(float x, float y) {
        GVector::x = x;
        GVector::y = y;
        return *this;
    }

    // установить в 0
    GVector& setZero() {
        return set(0, 0);
    }

    // повернуть на угол
    GVector& rotate(float rad) {
        float cosA = cosf(rad);
        float sinA = sinf(rad);
        return set(x * cosA - y * sinA, x * sinA + y * cosA);
    }

    // повернуть по направлению вектора
    GVector& rotateTo(const GVector& target) {
        return setHeading(target.heading());
    }

    // повернуть на +90°
    GVector& rotate90CCW() {
        return set(-y, x);
    }

    // повернуть на -90°
    GVector& rotate90CW() {
        return set(y, -x);
    }

    // повернуть на 180 (отразить вдоль себя)
    GVector& rotate180() {
        return set(-x, -y);
    }

    // отразить по оси Х
    GVector& reflectX() {
        return set(x, -y);
    }

    // отразить по оси Y
    GVector& reflectY() {
        return set(-x, y);
    }

    // отразить по нормали (должна быть нормализована)
    GVector& reflect(const GVector& normal) {
        return sub(normal * (2 * dot(normal)));
    }

    // нормализовать
    GVector& normalize() {
        return div(mag());
    }

    // установить длину
    GVector& setMag(float v) {
        float m = mag();
        return m ? mul(v / m) : set(0, 0);
    }

    // ограничить длину сверху
    GVector& limit(float mag) {
        float m = magSq();
        return (m > mag * mag) ? setMag(mag) : *this;
    }

    // ограничить длину в диапазоне
    GVector& clamp(float minm, float maxm) {
        float m = magSq();
        if (m < minm * minm) return setMag(minm);
        if (m > maxm * maxm) return setMag(maxm);
        return *this;
    }

    // установить направление
    GVector& setHeading(float rad) {
        float m = mag();
        return set(m * cosf(rad), m * sinf(rad));
    }

    // установить направление
    GVector& setHeadingDeg(int deg) {
        return setHeading(toRad(deg));
    }

    // интерполировать текущий вектор к v, где t — коэффициент от 0.0 до 1.0.
    GVector& lerp(const GVector& v, float t) {
        return set(x + (v.x - x) * t, y + (v.y - y) * t);
    }
};