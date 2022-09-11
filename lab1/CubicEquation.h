#ifndef MATH_CUBICEQUATION_H
#define MATH_CUBICEQUATION_H

#include <vector>
#include <string>
#include "QuadraticEquation.h"

struct Section {
    double left;
    double right;

    explicit Section(double left = 0, double right = 0) : left(left), right(right) {}
};

struct Root {
    double root;
    std::string termiante_condition;

    Root(double root, std::string condition) : root(root), termiante_condition(condition) {}
};

class CubicEquation {
    double _a, _b, _c, _d;

    std::vector<Root> cubic_equation_roots;

    double get_value(double x) const;

    Section localization(double start, double end, double delta);

public:

    CubicEquation(const double& a, const double& b, const double& c, const double& d): _a(a), _b(b), _c(c), _d(d) {}

    QuadraticEquation diff() const;

    std::vector<Root> get_roots();

    Root find_root(Section section, double eps);

    void solve(double delta, double eps);
};

#endif //MATH_CUBICEQUATION_H
