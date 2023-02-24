#include "tseitinTransformer.h"
#include "satSolver.h"
#include <iostream>
#include <stack>
#include <string>
using namespace std;
// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
/*int main() {
  while (true) // continuously asking for new inputs from standard input
  {
    std::string line; // store each input line
    // your code starts here
  }
}*/

int main() {
    while (true) // continuously asking for new inputs from standard input
    {
        std::string line; // store each input line
        if (!getline(cin, line)) // read input from standard input
       {
            break; // if EOF is reached, terminate gracefully
       }

       //auto ast = parse(line); // parse the input into an AST

       // parse the input into a syntax tree
      // auto ast = parse(line);
        // create a TseitinTransformer and transform the syntax tree
        TreeNode* ast = parse(line);
        //VariableNode node();
        TseitinTransformer transformer(ast);
        std::vector<std::vector<int>> cnf = transformer.transform();

        // solve the CNF formula using MiniSAT
        auto satSolution = satCallingMiniSat(transformer.getVarNum(), cnf);

       if (satSolution) // if a solution is found
      {
           if (satSolution==1)
           cout << "True" << endl; // output the solution
           else cout << "False" << endl;
      }
       else
      {
          cout << "UNSAT" << endl; // output "UNSAT" if no solution is found
      }

    }

    return 0;
}
