#pragma once

#include <functional>

namespace numerics {

// Параметры метода дихотомии (бисекции).
struct SolverParams {
    double a              = 0.0;   // левая граница отрезка
    double b              = 1.0;   // правая граница отрезка
    double tolerance      = 1e-9;  // критерий остановки
    int    max_iterations = 100;
};

// Результат работы солвера.
struct SolverResult {
    double root       = 0.0;
    int    iterations = 0;
    bool   converged  = false;
};

class BisectionSolver {
public:
    using Function = std::function<double(double)>;

    explicit BisectionSolver(SolverParams params = {});

    // Ищем корень f(x) = 0 на отрезке [a, b].
    // Метод требует, чтобы f(a) и f(b) имели разные знаки
    // (иначе наличие корня внутри отрезка не гарантировано).
    SolverResult solve(const Function& f) const;

    void set_params(const SolverParams& params);
    const SolverParams& params() const;

private:
    SolverParams params_;
};

}  // namespace numerics
