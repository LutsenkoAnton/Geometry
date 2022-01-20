#include "Rootnum.hpp"
#include <cmath>
#include <ostream>

std::pair<int, int> sqrt(int n) {
    std::map<int, int> divs;
    int i = 2;
    while (i * i <= n) {
        if (n % i == 0) {
            n /= i;
            divs[i]++;
        } else {
            i++;
        }
    }
    if (n > 1) {
        divs[n]++;
    }
    int a = 1, b = 1;
    for (auto [div, cnt] : divs) {
        if (cnt % 2 == 1) b *= div;
        for (int i = 0; i < cnt; i += 2) {
            a *= div;
        }
    }
    return {a, b};
}

std::pair<Fraction, int> sqrt(Fraction f) {
    auto [a, b] = sqrt(f.y);
    a *= b;
    f.x *= b;
    auto [c, d] = sqrt(f.x);
    return {Fraction(c, a), d};
}

Rootnum::Rootnum() {
    lvl = 0;
    lvl0data = Fraction();
}

Rootnum::Rootnum(int f) {
    lvl = 0;
    lvl0data = f;
}

Rootnum::Rootnum(Fraction f) {
    lvl = 0;
    lvl0data = f;
}

Rootnum::Rootnum(std::map<Rootnum, Fraction> val) {
    this -> lvl = 1;
    this -> val = val;
}

Rootnum Rootnum::operator-() {
    if (lvl == 0) {
        return Rootnum(-lvl0data);
    }
    auto cpy = val;
    for (auto &[a, b] : cpy) {
        b *= -1;
    }
    return Rootnum(std::move(cpy));
}

Rootnum Rootnum::operator+(Rootnum other) const {
    if (lvl == 0) {
        if (other.lvl == 0) {
            return Rootnum(lvl0data + other.lvl0data);
        }
        auto cpy = other.val;
        cpy[1] += lvl0data;
        return Rootnum(std::move(cpy));
    }
    if (other.lvl == 0) {
        auto cpy = val;
        cpy[1] += other.lvl0data;
        return Rootnum(std::move(cpy));
    }
    auto cpy = val;
    for (auto [a, b] : other.val) {
        cpy[a] += b;
    }
    return Rootnum(std::move(cpy));
}

Rootnum Rootnum::operator-(Rootnum other) const {
    return (*this)+(-other);
}

Rootnum Rootnum::operator*(Rootnum other) const {
    if (lvl == 0) {
        if (other.lvl == 0) {
                // std::cerr << (*this) << ' ' << other << std::endl;
            return Rootnum(lvl0data * other.lvl0data);
        }
        auto cpy = other.val;
        for (auto &[a, b] : cpy) {
            b *= lvl0data;
        }
        // for (auto [a,b] : cpy) {
        //     std::cerr << a << ' ' << b << std::endl;
        // }
        return Rootnum(std::move(cpy));
    }
    if (other.lvl == 0) {
        auto cpy = val;
        for (auto &[a, b] : cpy) {
            b *= other.lvl0data;
        }
        // std::cerr << (*this) << ' ' << other << std::endl;
        return Rootnum(std::move(cpy));
    }
    std::map<Rootnum, Fraction> cnt;
    for (auto &[a, b]: val) {
        for (auto &[x, y] : other.val) {
            cnt[a * x] += b * y;
        }
    }
    // std::cerr << (*this) << ' ' << other << std::endl;
    return Rootnum(std::move(cnt));
}

void Rootnum::operator+=(Rootnum other) {
    if (lvl == 0) {
        if (other.lvl == 0) {
            lvl0data += other.lvl0data;
            return;
        }
        lvl = 1;
        val[1] += lvl0data;
    }
    if (other.lvl == 0) {
        val[1] += other.lvl0data;
        return;
    }
    for (auto [a, b] : other.val) {
        val[a] += b;
    }
}

void Rootnum::operator-=(Rootnum other) {
    if (lvl == 0) {
        if (other.lvl == 0) {
            lvl0data -= other.lvl0data;
            return;
        }
        lvl = 1;
        val[1] -= lvl0data;
    }
    if (other.lvl == 0) {
        val[1] -= other.lvl0data;
        return;
    }
    for (auto [a, b] : other.val) {
        val[a] -= b;
    }
}

void Rootnum::operator*=(Rootnum other) {
    (*this) = (*this) * other;
}

Rootnum::operator double() const {
    if (lvl == 0) return lvl0data;
    double ans = 0;
    for (auto [a, b] : val) {
        ans += (double)b * std::sqrt((double)a);
    }
    return ans;
}

Rootnum sqrt(Rootnum r) {
    std::map<Rootnum, Fraction> m;
    m[r] += 1;
    return Rootnum(m);
}

std::ostream &operator<<(std::ostream &out, Rootnum r) {
    if (r.lvl == 0) {
        out << r.lvl0data;
        return out;
    }
    bool first = true;
    for (auto [a, b] : r.val) {
        if (!first) {
            out << " + ";
        } else {
            first = false;
        }

        if (abs((double)a - 1.0) < EPS) {
            if (b.y > 0) {
                out << b;
            } else {
                out << "(" << b << ")";
            }
            continue;
        }
        if (b != 1) {
            if (b.y > 0) {
                out << b << " * ";
            } else {
                out << "(" << b << ") * ";
            }
        }
        out << "sqrt(" << a << ")";
    }
    return out;
}