#ifndef ROOTFRACTION_HPP
#define ROOTFRACTION_HPP

#include "Rootnum.hpp"
#include <ostream>
#include <numeric>
#include <compare>

struct RootFraction {
    Rootnum x; // numerator
    Rootnum y; // denominator
    RootFraction();
    RootFraction(int x);
    void shorten();
    RootFraction(Rootnum x);
    RootFraction(Rootnum x, Rootnum y);
    RootFraction operator-();
    RootFraction operator+(RootFraction) const;
    RootFraction operator-(RootFraction) const;
    RootFraction operator*(RootFraction) const;
    RootFraction operator/(RootFraction) const;
    void operator+=(RootFraction);
    void operator-=(RootFraction);
    void operator*=(RootFraction);
    void operator/=(RootFraction);
    operator double() const;
};

RootFraction sqrt(RootFraction);
RootFraction abs(RootFraction);

std::ostream &operator<< (std::ostream &, RootFraction);

#endif