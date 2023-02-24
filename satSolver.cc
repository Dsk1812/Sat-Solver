#include "satSolver.h"
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"

bool satCallingMiniSat(unsigned int numVar, std::vector<std::vector<int>> &cnf) {
  // Create a MiniSat solver object
  Minisat::Solver solver;

  // Add variables to the solver
  for (unsigned int i = 0; i < numVar; ++i) {
    solver.newVar();
  }

  // Add clauses to the solver
  for (const auto &clause : cnf) {
    // Create a MiniSat vector of literals
    Minisat::vec<Minisat::Lit> lits;

    // Convert the clause to a vector of literals
    for (const auto &literal : clause) {
      // The literal is negated if it is negative
      if (literal < 0) {
        lits.push(Minisat::mkLit(std::abs(literal) - 1, true));
      } else {
        lits.push(Minisat::mkLit(literal - 1, false));
      }
    }

    // Add the clause to the solver
    solver.addClause(lits);
  }

  // Solve the problem and return the result
  return solver.solve();
}

