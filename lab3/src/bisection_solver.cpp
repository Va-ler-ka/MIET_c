#include "numerics/bisection_solver.hpp"

#include <cmath>
#include <stdexcept>
#include <utility>

namespace numerics {

BisectionSolver::BisectionSolver(SolverParams params) : params_(params) {}

void BisectionSolver::set_params(const SolverParams& params) { params_ = params; }

const SolverParams& BisectionSolver::params() const { return params_; }

SolverResult BisectionSolver::solve(const Function& f) const {
    if (!f) {
        throw std::invalid_argument("BisectionSolver::solve: функция f не задана");
    }

    double a = params_.a;
    double b = params_.b;

    if (a > b) {
        std::swap(a, b);
    }

    double fa = f(a);
    double fb = f(b);

    // границы отрезка сами могут оказаться корнем
    if (std::abs(fa) < params_.tolerance) {
        return SolverResult{a, 0, true};
    }
    if (std::abs(fb) < params_.tolerance) {
        return SolverResult{b, 0, true};
    }

    if (fa * fb > 0.0) {
        throw std::invalid_argument(
            "BisectionSolver::solve: f(a) и f(b) должны иметь разные знаки");
    }

    double c = a;

    for (int iter = 0; iter < params_.max_iterations; ++iter) {
        c = 0.5 * (a + b);
        const double fc = f(c);

        if (std::abs(fc) < params_.tolerance || 0.5 * (b - a) < params_.tolerance) {
            return SolverResult{c, iter, true};
        }

        if (fa * fc < 0.0) {
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }
    }

    return SolverResult{c, params_.max_iterations, false};
}

}  // namespace numerics
