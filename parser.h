#include "treeNode.h"
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
TreeNode* parse(const std::string& input)
{
    // use a stack to store intermediate nodes as we parse the input string
    std::stack<TreeNode*> nodeStack;

    // iterate through the input string
    for (char c : input)
    {
        if (c == ' ') // ignore spaces
        {
            continue;
        }

        if (c == '(') // push a new operator node onto the stack
        {
            nodeStack.push(new OperatorNode("", 0, ' '));
        }
        else if (c == ')') // pop the top two nodes from the stack and make them the children of the operator node at the top of the stack
        {
            TreeNode* right = nodeStack.top();
            nodeStack.pop();
            TreeNode* left = nodeStack.top();
            nodeStack.pop();
            TreeNode* op = nodeStack.top();
            nodeStack.pop();
            op->setLeftChild(left);
            op->setRightChild(right);
            nodeStack.push(op);
        }
        else if (c == '|' || c == '&' || c == '!') // update the operator of the operator node at the top of the stack
        {
            nodeStack.top()->setOp(c);
        }
        else // push a new variable node onto the stack
        {
            
            std::string var;
            var += c;
            VariableNode node(var);
    		std::string cont = node.getContent();
            nodeStack.push(cont);
        }
    }

    // the root of the AST is the only node remaining on the stack
    TreeNode* root = nodeStack.top();
    nodeStack.pop();
    return root;
}
