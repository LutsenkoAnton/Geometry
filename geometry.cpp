#include "geometry.hpp"
#include <algorithm>
#include <cmath>
#include <ostream>

Point::Point() {
	x = 0;
	y = 0;
	z = 0;
}
Point::Point(geomt x, geomt y, geomt z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

std::ostream &operator<<(std::ostream &out, Point p) {
	out << p.x << ' ' << p.y << ' ' << p.z;
	return out;
}

geomt dist2(Point a, Point b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z);
}

geomt dist(Point a, Point b) {
	return sqrt(dist2(a, b));
}

Vector::Vector() {
	x = 0;
	y = 0;
	z = 0;
}
Vector::Vector(geomt x, geomt y, geomt z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
Vector::Vector(Point a, Point b) {
	this->x = b.x - a.x;
	this->y = b.y - a.y;
	this->z = b.z - a.z;
}
geomt Vector::operator*(Vector other) {
	return x * other.x + y * other.y + z * other.z;
}

Vector Vector::operator*(geomt num) {
    return Vector(x * num, y * num, z * num);
}

geomt Vector::size2() {
	return x * x + y * y + z * z;
}

geomt Vector::size() {
	return sqrt(size2());
}

Vector operator*(geomt num, Vector v) {
    return v * num;
}

Point operator+(Point p, Vector v) {
    return Point(p.x + v.x, p.y + v.y, p.z + v.z);
}

std::ostream &operator<<(std::ostream &out, Vector p) {
	out << p.x << ' ' << p.y << ' ' << p.z;
	return out;
}

Plane::Plane() {
	a = 1;
	b = 0;
	c = 0;
	d = 0;
}
Plane::Plane(geomt a, geomt b, geomt c, geomt d) {
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
}
Plane::Plane(Point a, Point b, Point c) {
	if (a.x == 0 && b.x == 0 && c.x == 0) {
		this->a = 1;
		this->b = 0;
		this->c = 0;
		this->d = 0;
		return;
	}
	if (a.x == 0 && b.x == 0) {
		std::swap(a, c);
	} else if (a.x == 0) {
		std::swap(a, b);
	}
	b.y -= b.x * a.y / a.x;
	b.z -= b.x * a.z / a.x;
	geomt bd = RootFraction(1) - b.x / a.x;
	b.x = 0;
	c.y -= c.x * a.y / a.x;
	c.z -= c.x * a.z / a.x;
	geomt cd = RootFraction(1) - c.x / a.x;
	c.x = 0;
	if (b.y == 0 && c.y == 0) {
		this->d = 0;
		this->c = 0;
		this->b = 1;
		this->a = -this->b * a.y / a.x;
		return;
	}
	if (b.y == 0)
		std::swap(b, c);
	c.z -= c.y * b.z / b.y;
	cd -= bd * c.y / b.y;
	c.y = 0;
	if (c.z == 0) {
		this->d = 0;
		this->c = 1;
		this->b = -this->c * b.z / b.y;
		this->a = (-this->c * a.z - this->b * a.y) / a.x;
		return;
	}
	this->d = 1;
	this->c = -this->d * cd / c.z;
	this->b = (-this->d * bd - this->c * b.z) / (b.y);
	this->a = (-this->d - this->c * a.z - this->b * a.y) / a.x;
}

std::ostream &operator<<(std::ostream &out, Plane p) {
	out << p.a << "x";
    if ((double)p.b >= 0) {
        out << " + " << p.b << "y";
    } else {
        out << " - " << -p.b << "y";
    }
    if ((double)p.c >= 0) {
        out << " + " << p.c << "z";
    } else {
        out << " - " << -p.c << "z";
    }
    if ((double)p.d >= 0) {
        out << " + " << p.d;
    } else {
        out << " - " << -p.d;
    }
    out << " = 0";
	return out;
}

Vector Plane::norm() {
	return Vector(a, b, c);
}

Point otnosh(Point a, Point b, geomt otna, geomt otnb) {
	return Point((a.x * otnb + b.x * otna) / (otna + otnb), (a.y * otnb + b.y * otna) / (otna + otnb), (a.z * otnb + b.z * otna) / (otna + otnb));
}

geomt dist(Point a, Plane p) {
	return (p.a * a.x + p.b * a.y + p.c * a.z + p.d) / p.norm().size();
}

geomt angle(Vector a, Vector b) {
	return abs(a * b) / a.size() / b.size();
}

geomt angle(Vector v, Plane p) {
    return (geomt)1 - angle(v, p.norm()) * angle(v, p.norm());
}

geomt angle(Plane p, Vector v) {
    return angle(v, p);
}

geomt angle(Plane a, Plane b) {
    return angle(a.norm(), b.norm());
}