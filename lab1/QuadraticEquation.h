#ifndef MATH_QUADRATICEQUATION_H
#define MATH_QUADRATICEQUATION_H

class QuadraticEquation {
    double _a, _b, _c;

public:
    struct Roots {
        unsigned int count;
        double root1, root2;
        Roots(const unsigned int& count, const double& root1 = 0, const double& root2 = 0) : count(count), root1(root1), root2(root2) {}
    };

    QuadraticEquation(const double& a, const double& b, const double& c): _a(a), _b(b), _c(c) {}

    double discriminant() const;

    Roots solve() const;
};


#endif //MATH_QUADRATICEQUATION_H
