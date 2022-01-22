#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "RootFraction.hpp"
#include <ostream>

typedef RootFraction geomt;

struct Point {
    geomt x, y, z;
    Point();
    Point(geomt x, geomt y, geomt z);
};

std::ostream &operator<<(std::ostream&, Point);

geomt dist2(Point, Point);

struct Vector {
    geomt x, y, z;
    Vector();
    Vector(geomt, geomt, geomt);
    Vector(Point, Point);
    Vector operator-();
    Vector operator+(Vector);
    Vector operator-(Vector);
    geomt operator*(Vector);
    Vector operator*(geomt);
    geomt size2();
    geomt size();
};

Vector operator*(geomt, Vector);

Point operator+(Point, Vector);

std::ostream &operator<<(std::ostream &, Vector);

struct Plane {
    geomt a, b, c, d;
    Plane();
    Plane(geomt, geomt, geomt, geomt);
    Plane(Point, Point, Point);
    Vector norm();
};

std::ostream &operator<<(std::ostream &, Plane);

struct Line {
    Point a, b;

    Line();
    Line(Point, Point);

    Vector napr();
    operator Vector();
};

std::ostream &operator<<(std::ostream &, Line);

Point otnosh(Point, Point, geomt, geomt);

geomt dist(Point, Point); 
geomt dist(Point, Plane); 
geomt dist(Point, Line); 
geomt dist(Line, Line); 

geomt angle(Vector, Vector);
geomt angle(Vector, Plane);
geomt angle(Plane, Vector);
geomt angle(Plane, Plane);
#endif