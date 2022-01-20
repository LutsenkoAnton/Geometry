#include "Fraction.hpp"
#include <stdexcept>

Fraction::Fraction() {
    x = 0;
    y = 1;
}

Fraction::Fraction(int x) {
    this -> x = x;
    y = 1;
}

void Fraction::shorten() {
    int g = std::gcd(x, y);
    x = x / g;
    y = y / g;
    if (y < 0) {
        x *= -1;
        y *= -1;
    }
}

Fraction::Fraction(int x, int y) {
    if (y == 0) {
        throw std::runtime_error("Division by zero is forbidden");
    }
    if (y < 0) {
        x *= -1;
        y *= -1;
    }
    this -> x = x;
    this -> y = y;
    shorten();
}

Fraction Fraction::operator-() {
    return Fraction(-x, y);
}

Fraction Fraction::operator+(Fraction other) const {
    return Fraction(x * other.y + y * other.x, y * other.y);
}

Fraction Fraction::operator-(Fraction other) const {
    return *this + (-other);
}

Fraction Fraction::operator*(Fraction other) const {
    return Fraction(x * other.x, y * other.y);
}

Fraction Fraction::operator/(Fraction other) const {
    return Fraction(x * other.y, y * other.x);
}

void Fraction::operator+=(Fraction other) {
    x = x * other.y + y * other.x;
    y = y * other.y;
    shorten();
}

void Fraction::operator-=(Fraction other) {
    (*this) += (-other);
}

void Fraction::operator*=(Fraction other) {
    x *= other.x;
    y *= other.y;
    shorten();
}

void Fraction::operator/=(Fraction other) {
    x *= other.y;
    y *= other.x;
    if (y == 0) {
        throw std::runtime_error("Division by zero is forbidden");
    }
    shorten();
}

std::strong_ordering Fraction::operator<=>(Fraction other) {
    return (x * other.y <=> y * other.x);
}

Fraction::operator double() const {
    return (double) x / y;
}

std::ostream &operator<<(std::ostream &out, Fraction f) {
    if (f.y == 1) {
        out << f.x;
        return out;
    }
    out << f.x << "/" << f.y;
    return out;
}