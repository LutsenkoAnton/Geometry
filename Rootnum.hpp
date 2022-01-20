#ifndef ROOTNUM_HPP
#define ROOTNUM_HPP
#include "Fraction.hpp"

#include <map>
#include <compare>
#include <utility>
#include <ostream>

constexpr double EPS = 1e-6;

std::pair<int, int> sqrt(int);
std::pair<Fraction, int> sqrt(Fraction);

struct Rootnum {
    int lvl;
    Fraction lvl0data;
    std::map<Rootnum, Fraction> val;
    Rootnum();
    Rootnum(int);
    Rootnum(Fraction);
    Rootnum(std::map<Rootnum, Fraction>);
    Rootnum operator-();
    Rootnum operator+(Rootnum) const;
    Rootnum operator-(Rootnum) const;
    Rootnum operator*(Rootnum) const;
    void operator+=(Rootnum);
    void operator-=(Rootnum);
    void operator*=(Rootnum);
    operator double() const;
};

Rootnum sqrt(Rootnum);

std::ostream &operator<<(std::ostream &, Rootnum);

#endif