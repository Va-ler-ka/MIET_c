#include <iomanip>
#include <iostream>

#include "numerics/bisection_solver.hpp"

int main() {
    numerics::SolverParams params;
    params.a = 0.0;
    params.b = 2.0;
    params.tolerance = 1e-10;
    params.max_iterations = 100;

    numerics::BisectionSolver solver(params);

    // Для примера ищем корень x^2 - 2 = 0 на отрезке [0, 2], то есть sqrt(2)
    auto result = solver.solve([](double x) { return x * x - 2.0; });

    std::cout << std::setprecision(10)
              << "root = " << result.root
              << ", iterations = " << result.iterations
              << ", converged = " << std::boolalpha << result.converged
              << '\n';

    return 0;
}
