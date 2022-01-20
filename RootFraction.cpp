#include "RootFraction.hpp"
#include <stdexcept>
#include <ostream>

RootFraction::RootFraction() {
    x = 0;
    y = 1;
}

RootFraction::RootFraction(int x) {
    this -> x = x;
    y = 1;
}

RootFraction::RootFraction(Rootnum r) {
    this -> x = r;
    y = 1;
}

void RootFraction::shorten() {
    if (x.lvl == 0 && y.lvl == 0) {
        auto f = (x.lvl0data / y.lvl0data);
        this -> x = f.x;
        this -> y = f.y;
    }
    if (y < 0) {
        x *= -1;
        y *= -1;
    }
}

RootFraction::RootFraction(Rootnum x, Rootnum y) {
    if (abs((double)y) < EPS) {
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

RootFraction RootFraction::operator-() {
    return RootFraction(-x, y);
}

RootFraction RootFraction::operator+(RootFraction other) const {
    return RootFraction(x * other.y + y * other.x, y * other.y);
}

RootFraction RootFraction::operator-(RootFraction other) const {
    return *this + (-other);
}

RootFraction RootFraction::operator*(RootFraction other) const {
    return RootFraction(x * other.x, y * other.y);
}

RootFraction RootFraction::operator/(RootFraction other) const {
    return RootFraction(x * other.y, y * other.x);
}

void RootFraction::operator+=(RootFraction other) {
    x = x * other.y + y * other.x;
    y = y * other.y;
    shorten();
}

void RootFraction::operator-=(RootFraction other) {
    (*this) += (-other);
}

void RootFraction::operator*=(RootFraction other) {
    x *= other.x;
    y *= other.y;
    shorten();
}

void RootFraction::operator/=(RootFraction other) {
    x *= other.y;
    y *= other.x;
    if (y == 0) {
        throw std::runtime_error("Division by zero is forbidden");
    }
    shorten();
}

RootFraction::operator double() const {
    return (double) x / y;
}

RootFraction sqrt(RootFraction f) {
    return RootFraction(sqrt(f.x), sqrt(f.y));
}

RootFraction abs(RootFraction f) {
    if ((double)f < 0) {
        f *= -1;
    }
    return f;
}

std::ostream &operator<<(std::ostream &out, RootFraction f) {
    if (std::abs((double)f.y - 1.0) < EPS) {
        out << f.x;
        return out;
    }
    if (f.x.lvl == 0 || f.x.val.size() == 1) {
        out << f.x;
    } else {
        out <<"(" << f.x << ")";
    }
    out << "/";
    if ((f.y.lvl == 0 && f.y > 0) || (f.y.val.size() == 1 && f.y.val.begin() -> second == 1)) {
        out << f.y;
    } else {
        out <<"(" << f.y << ")";
    }
    return out;
}