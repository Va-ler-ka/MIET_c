#include <gtest/gtest.h>

#include <cmath>
#include <stdexcept>

#include "numerics/bisection_solver.hpp"

TEST(BisectionSolverTest, FindsSquareRootOfTwo) {
    numerics::SolverParams params;
    params.a = 0.0;
    params.b = 2.0;
    params.tolerance = 1e-10;
    params.max_iterations = 100;

    numerics::BisectionSolver solver(params);
    auto result = solver.solve([](double x) { return x * x - 2.0; });

    ASSERT_TRUE(result.converged);
    EXPECT_NEAR(result.root, std::sqrt(2.0), 1e-8);
}

TEST(BisectionSolverTest, FindsRootOfCubicFunction) {
    // x^3 - x - 2 = 0, корень x ≈ 1.5213797
    numerics::SolverParams params;
    params.a = 1.0;
    params.b = 2.0;
    params.tolerance = 1e-9;
    params.max_iterations = 200;

    numerics::BisectionSolver solver(params);
    auto result = solver.solve([](double x) { return x * x * x - x - 2.0; });

    ASSERT_TRUE(result.converged);
    EXPECT_NEAR(result.root, 1.5213797, 1e-6);
}

TEST(BisectionSolverTest, ReportsNonConvergenceWhenMaxIterationsTooSmall) {
    numerics::SolverParams params;
    params.a = 0.0;
    params.b = 2.0;
    params.tolerance = 1e-15;
    params.max_iterations = 1;

    numerics::BisectionSolver solver(params);
    auto result = solver.solve([](double x) { return x * x - 2.0; });

    EXPECT_FALSE(result.converged);
}

TEST(BisectionSolverTest, ThrowsWhenSignsAreEqual) {
    numerics::SolverParams params;
    params.a = 0.0;
    params.b = 1.0;  // f(0) = -2, f(1) = -1 — оба отрицательные

    numerics::BisectionSolver solver(params);

    EXPECT_THROW(
        solver.solve([](double x) { return x * x - 2.0; }),
        std::invalid_argument);
}

TEST(BisectionSolverTest, TighterToleranceRequiresMoreIterations) {
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

    ASSERT_TRUE(loose_result.converged);
    ASSERT_TRUE(tight_result.converged);
    EXPECT_GT(tight_result.iterations, loose_result.iterations);
}
