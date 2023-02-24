#include "tseitinTransformer.h"
//std::vector<int> clauses_;
TseitinTransformer::TseitinTransformer(TreeNode *root): formulaRoot{root} {}
// int varNum = 0;
/*int TseitinTransformer::transSubformula(TreeNode* subRoot) {
  // your code starts here
  return 0;
}*/
void TseitinTransformer::addImplication(int a, int b)
{
    // add the clauses (a or !b) and (!a or b)
    cnf.push_back({a, -b});
    cnf.push_back({-a, b});
}

int TseitinTransformer::transSubformula(TreeNode* subRoot)
{
    // if the subformula is a leaf node (i.e., a variable), return its ID
    if (subRoot->isLeaf())
    {
        // check if the variable already has an ID
        auto it = varIdTable.find(subRoot->getContent());
        if (it != varIdTable.end())
        {
            // return the existing ID
            return it->second;
        }
        else
        {
            // assign a new ID and add it to the table
            int varId = varIdCounter++;
            varIdTable[subRoot->getContent()] = varId;
            return varId;
        }
    }

    // if the subformula is not a leaf node, create a new variable for it
    int curId = varIdCounter++;

    // recursively transform the left and right children of the subformula
    int leftId = transSubformula(subRoot->getLeftChild());
    int rightId = transSubformula(subRoot->getRightChild());

    // add the appropriate clauses for the current subformula based on its operator
    char op = subRoot->getOp();
    if (op == '!')
    {
        addNegEq(curId, leftId);
    }
    else if (op == '|')
    {
        addOrEq(curId, leftId, rightId);
    }
    else if (op == '&')
    {
        addAndEq(curId, leftId, rightId);
    }
    else
    {
        throw std::invalid_argument("Invalid operator: " + op);
    }

    return curId;
}

/*
void TseitinTransformer::addNegEq(int curID, int childID) {
  // your code starts here
}*/
void TseitinTransformer::addNegEq(int curID, int childID)
{
    // add the clauses (!curID or !childID) and (curID or childID)
    cnf.push_back({-curID, -childID});
    cnf.push_back({curID, childID});
}

/*
void TseitinTransformer::addOrEq(int curID, int leftID, int rightID) {
  // your code starts here
}*/
void TseitinTransformer::addOrEq(int curID, int leftID, int rightID)
{
    // add the clauses (curID or !leftID or !rightID), (!curID or leftID), and (!curID or rightID)
    cnf.push_back({curID, -leftID, -rightID});
    cnf.push_back({-curID, leftID});
    cnf.push_back({-curID, rightID});
}

/*
void TseitinTransformer::addAndEq(int curID, int leftID, int rightID) {
  // your code starts here
}
*/
void TseitinTransformer::addAndEq(int curID, int leftID, int rightID)
{
    // add the clauses (!curID or !leftID or !rightID), (curID or !leftID), and (curID or !rightID)
    cnf.push_back({-curID, -leftID, -rightID});
    cnf.push_back({curID, -leftID});
    cnf.push_back({curID, -rightID});
}

/*
std::vector<std::vector<int>> TseitinTransformer::transform() {
  // your code starts here
  return cnf;
}*/
std::vector<std::vector<int>> TseitinTransformer::transform()
{
    // reset the variable ID counter and table
    varIdCounter = 1;
    varIdTable.clear();

    // transform the root formula
    transSubformula(formulaRoot);

    // return the resulting CNF
    return cnf;
}

/*
std::string TseitinTransformer::cnfString() const {
  std::string result = "";
  // your code starts here
  return result;
}*/
std::string TseitinTransformer::cnfString() const
{
    std::stringstream ss;
    for (const auto& clause : cnf)
    {
        for (int var : clause)
        {
            ss << var << " ";
        }
        ss << "0\n";
    }
    return ss.str();
}
/*
unsigned int TseitinTransformer::getVarNum() const {
  // your code starts here
  return 0;
}*/
unsigned int TseitinTransformer::getVarNum() const
{
    return varIdCounter - 1; // subtract 1 because the counter starts at 1
}
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
            nodeStack.push(new VariableNode(var));
        }
    }

    // the root of the AST is the only node remaining on the stack
    TreeNode* root = nodeStack.top();
    nodeStack.pop();
    return root;
}

