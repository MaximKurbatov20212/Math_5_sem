#include <iostream>
#include <cmath>
#include <vector>
#include "CubicEquation.h"

int main(int argc, char* argv[]) {

    CubicEquation cubic_equation = CubicEquation(1, atof(argv[3]), atof(argv[4]), atof(argv[5]));
    cubic_equation.solve(atof(argv[1]), atof(argv[2]));

    std::vector<Root> roots = cubic_equation.get_roots();
    for(const Root& i : roots) {
        std::cout << "root " << i.root << "\nTerminate condition: " << i.termiante_condition << std::endl << std::endl;
    }

    return 0;
}
