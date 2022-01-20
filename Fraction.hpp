#ifndef FRACTION_HPP
#define FRACTION_HPP
#include <ostream>
#include <numeric>
#include <compare>

struct Fraction {
    int x; // numerator
    int y; // denominator
    Fraction();
    Fraction(int x);
    void shorten();
    Fraction(int x, int y);
    Fraction operator-();
    Fraction operator+(Fraction) const;
    Fraction operator-(Fraction) const;
    Fraction operator*(Fraction) const;
    Fraction operator/(Fraction) const;
    void operator+=(Fraction);
    void operator-=(Fraction);
    void operator*=(Fraction);
    void operator/=(Fraction);
    std::strong_ordering operator<=>(Fraction);
    operator double() const;
};

std::ostream &operator<< (std::ostream &, Fraction);

#endif