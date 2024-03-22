#include "Vector.h"

Vector::Vector(int i) : elem{new double[i]}, sz(i) {}

int Vector::size() { return sz; }

double &Vector::operator[](int i) { return elem[i]; }