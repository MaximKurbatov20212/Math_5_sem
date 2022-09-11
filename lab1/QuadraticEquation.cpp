#include <valarray>
#include "QuadraticEquation.h"

    double QuadraticEquation::discriminant() const {
        return _b * _b - 4 * _a * _c;
    }

    QuadraticEquation::Roots QuadraticEquation::solve() const {
        double disc = discriminant();
        if (disc < 0) return Roots(0);
        else if (disc == 0) return Roots(1, (-_b) / (2 * _a));
        else return Roots(2, ((-_b) - std::sqrt(disc)) / (2 * _a),  ((-_b) + std::sqrt(disc)) / (2 * _a));
    }
