#include <cmath>
#include <cfloat>
#include "CubicEquation.h"

QuadraticEquation CubicEquation::diff() const {
    return QuadraticEquation(3 * _a, 2 * _b, _c);
}

std::vector<Root> CubicEquation::get_roots() {
    return cubic_equation_roots;
}

double CubicEquation::get_value(double x) const {
    return _a * x * x * x + _b * x * x + _c * x + _d;
}

Section CubicEquation::localization(double start, double end, double delta) {
    int direction = end > start ? 1 : -1;

    while (true) {
        double first = get_value(start);
        double second = get_value(start + delta * direction);
        if (first * second <= 0) {
            return Section(fmin(start, start + delta * direction), fmax(start, start + delta * direction));
        }
        start = start + delta * direction;
    }
}

Root CubicEquation::find_root(Section section, double eps) {
    double value_in_center = 0;
    double c = (section.left + section.right) / 2;

    while (fabs(value_in_center = get_value(c)) >= eps) {
        if (value_in_center > eps) section.right = c;
        else section.left = c;
        c = (section.left + section.right) / 2;
    }
    return Root(c, "|f(" + std::to_string(c) + ")| = " + std::to_string(value_in_center) + " < " + std::to_string(eps));
}

void CubicEquation::solve(double delta, double eps) {
    QuadraticEquation q = diff();
    QuadraticEquation::Roots roots = q.solve();

    Section section;

    if (roots.count == 0 || roots.count == 1) {
        if (fabs(get_value(0)) < eps) {
            cubic_equation_roots.emplace_back(0, "|f(" + std::to_string(0) + ")" = std::to_string(get_value(0)) + "<" + std::to_string(eps));
            return;
        }

        else if (get_value(0) < -eps) {
            section = localization(0, DBL_MAX, delta);
        }
        else {
            section = localization(DBL_MIN, 0, delta);
        }

        cubic_equation_roots.emplace_back(find_root(section, eps));
        return;
    }

    else if (roots.count == 2) {
        double alpha = fmin(roots.root1, roots.root2);
        double beta = fmax(roots.root1, roots.root2);

//            f(a) > e && f(b) > e
        if (get_value(alpha) > eps && get_value(beta) > eps) {
            section = localization(alpha, DBL_MIN, delta);
            cubic_equation_roots.emplace_back(find_root(section, eps));
        }
//            f(a) < -e && f(b) < -e
        else if (get_value(alpha) < -eps && get_value(beta) < -eps) {
            section = localization(beta,DBL_MAX, delta);
            cubic_equation_roots.emplace_back(find_root(section, eps));
        }
//            f(a) > e && |f(b)| < e
        else if (get_value(alpha) > eps && fabs(get_value(beta)) < eps) {
            cubic_equation_roots.emplace_back(beta, "f(" + std::to_string(alpha) + ") = " + std::to_string(
                    get_value(alpha)) + " > " + std::to_string(eps) + "&&" + "|f(" + std::to_string(beta) + "|) = " + std::to_string(
                    get_value(beta)) + " < " + std::to_string(eps));
            section = localization(alpha, DBL_MIN, delta);
            cubic_equation_roots.emplace_back(find_root(section, eps));
        }
//            |f(a)| < e && f(b) < -e
        else if (fabs(get_value(alpha)) < eps && (get_value(beta) < -eps)) {
            cubic_equation_roots.emplace_back(alpha, "|f(" + std::to_string(alpha) + "|) = " + std::to_string(
                    get_value(alpha)) + " < " + std::to_string(eps) + " && " + "f(" + std::to_string(beta) + ") = " + std::to_string(
                    get_value(beta)) + " < -" + std::to_string(eps));

            section = localization(beta, DBL_MAX, delta);
            cubic_equation_roots.emplace_back(find_root(section, eps));
        }
//            f(a) > e && f(b) < -e
        else if (get_value(alpha) > eps && get_value(beta) < -eps) {
            section = localization(alpha, DBL_MIN, delta);
            cubic_equation_roots.emplace_back(find_root(section, eps));

            section = localization(alpha, beta, delta);
            cubic_equation_roots.emplace_back(find_root(section, eps));

            section = localization(beta, DBL_MAX, delta);
            cubic_equation_roots.emplace_back(find_root(section, eps));
        }

        else if (fabs(get_value(alpha)) < eps && fabs(get_value(beta)) < eps) {
            cubic_equation_roots.emplace_back(Root((alpha + beta) / 2, "|f(" + std::to_string(alpha) + "|) = " + std::to_string(
                    get_value(alpha)) + " < " + std::to_string(eps) + " && " + "|f(" + std::to_string(beta) + "|) = " + std::to_string(
                    get_value(beta)) + " < " + std::to_string(eps)));
        }
    }
}

