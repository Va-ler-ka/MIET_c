#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <cmath>
#include <stdexcept>

#include "numerics/bisection_solver.hpp"

using Catch::Matchers::WithinAbs;

TEST_CASE("Bisection method finds sqrt(2) on [0, 2]", "[bisection]") {
    numerics::SolverParams params;
    params.a = 0.0;
    params.b = 2.0;
    params.tolerance = 1e-10;
    params.max_iterations = 100;

    numerics::BisectionSolver solver(params);
    auto result = solver.solve([](double x) { return x * x - 2.0; });

    REQUIRE(result.converged);
    REQUIRE_THAT(result.root, WithinAbs(std::sqrt(2.0), 1e-8));
}

TEST_CASE("Bisection method finds root of a cubic function", "[bisection]") {
    // x^3 - x - 2 = 0, корень x ≈ 1.5213797
    numerics::SolverParams params;
    params.a = 1.0;
    params.b = 2.0;
    params.tolerance = 1e-9;
    params.max_iterations = 200;

    numerics::BisectionSolver solver(params);
    auto result = solver.solve([](double x) { return x * x * x - x - 2.0; });

    REQUIRE(result.converged);
    REQUIRE_THAT(result.root, WithinAbs(1.5213797, 1e-6));
}

TEST_CASE("Bisection method reports non-convergence when max_iterations is too small",
          "[bisection][edge-case]") {
    numerics::SolverParams params;
    params.a = 0.0;
    params.b = 2.0;
    params.tolerance = 1e-15;
    params.max_iterations = 1;

    numerics::BisectionSolver solver(params);
    auto result = solver.solve([](double x) { return x * x - 2.0; });

    REQUIRE_FALSE(result.converged);
}

TEST_CASE("Bisection method throws when f(a) and f(b) have the same sign",
          "[bisection][edge-case]") {
    numerics::SolverParams params;
    params.a = 0.0;
    params.b = 1.0;  // f(0) = -2, f(1) = -1 — оба отрицательные

    numerics::BisectionSolver solver(params);

    REQUIRE_THROWS_AS(
        solver.solve([](double x) { return x * x - 2.0; }),
        std::invalid_argument);
}

TEST_CASE("Tighter tolerance requires more iterations", "[bisection]") {
    numerics::SolverParams loose;
    loose.a = 0.0;
    loose.b = 2.0;
    loose.tolerance = 1e-3;
    loose.max_iterations = 100;

    numerics::SolverParams tight;
    tight.a = 0.0;
    tight.b = 2.0;
    tight.tolerance = 1e-9;
    tight.max_iterations = 100;

    numerics::BisectionSolver loose_solver(loose);
    numerics::BisectionSolver tight_solver(tight);

    auto loose_result = loose_solver.solve([](double x) { return x * x - 2.0; });
    auto tight_result = tight_solver.solve([](double x) { return x * x - 2.0; });

    REQUIRE(loose_result.converged);
    REQUIRE(tight_result.converged);
    REQUIRE(tight_result.iterations > loose_result.iterations);
}
