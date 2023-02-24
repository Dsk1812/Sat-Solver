#ifndef TNODE_H
#define TNODE_H

#include <string>

// abstract superclass of the syntax tree node
/*class TreeNode {
    std::string content;
    TreeNode *leftChild = nullptr;
    TreeNode *rightChild = nullptr;

  public:
    TreeNode(std::string cntt);
    // your code starts here

};*/

class TreeNode {
    std::string content;
    TreeNode *leftChild = nullptr;
    TreeNode *rightChild = nullptr;

  public:
    //TreeNode() :  {}
    TreeNode(std::string cntt,int value, char op) : content(cntt), value(value), left(nullptr), op(op), right(nullptr), varID(0){}
     enum class Operator { Negation, Conjunction, Disjunction };
    virtual ~TreeNode() {
        delete leftChild;
        delete rightChild;
    }
    char getOp() const  // define getOp() function
    {
        return op;  // return the value of the op member
    }
    void setOp(char op) {
        this->op = op;
    }
    void setContent(std::string op) {
        this->content = content;
    }
    std::string getContent() const { return content; }

    void setLeftChild(TreeNode *node) { leftChild = node; }
    TreeNode *getLeftChild() const { return leftChild; }

    void setRightChild(TreeNode *node) { rightChild = node; }
    TreeNode *getRightChild() const { return rightChild; }
    bool isLeaf() const  // define isLeaf() function
    {
        return (left == nullptr && right == nullptr);  // return true if the node has no children
    }
    int getVarID() const  // define getVarID() function
    {
        return varID;  // return the value of the varID member
    }
    private:
    int value;
    char op;
    char* cntt;
    TreeNode* left;
    TreeNode* right;
    int varID;
};


// concrete tree node of opertaor type
/*class OperatorNode : public TreeNode {
  public:
    OperatorNode(std::string cntt);
    // your code starts here
};*/

class OperatorNode : public TreeNode {
public:
    OperatorNode(std::string cntt, int value, char op) : TreeNode(cntt, value, op) {}
    std::string getContent() {
        return content;
    }
    void setContent(std::string cntt) {
        content = cntt;
    }
    TreeNode* getLeft() {
        return left;
    }
    void setLeft(TreeNode* lft) {
        left = lft;
    }
    TreeNode* getRight() {
        return right;
    }
    void setRight(TreeNode* rght) {
        right = rght;
    }
private:
    std::string content;
    TreeNode* left;
    TreeNode* right;
};

/*
OperatorNode::OperatorNode(std::string cntt) {
    content = cntt;
    left = nullptr;
    right = nullptr;
}*/
// concrete tree node of varibale type
/*class VariableNode : public TreeNode {
  public:
    VariableNode(std::string cntt);
    // your code starts here
};*/
/*class VariableNode : public TreeNode {
  public:
    VariableNode(std::string cntt) : TreeNode(cntt) {}

    // Override the `evaluate` method to return the value of the variable
    double evaluate() const override {
      // Look up the value of the variable in the symbol table
      return SymbolTable::getInstance().getValue(getContent());
    }
};*/

class VariableNode : public TreeNode {
    public:
        // Define the constructor for VariableNode
        VariableNode(std::string cntt) : TreeNode(cntt, 0, ' ') {
    content = cntt;
}

        std::string getContent() const{
    return content;
};

    private:
        std::string content;
};

/*
VariableNode::VariableNode(std::string cntt) : content(cntt) {}

std::string VariableNode::getContent() const {
    return content;
}
*/
#endif
