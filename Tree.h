#ifndef TREE_H
#define TREE_H
struct Node{
    int data;
    Node* left;
    Node* right;
};
class Tree{
    private:
        Node* root;
        int height(Node* parent);
        int heightDifference(Node* parent);
        Node* llRotate(Node*& parent);
        Node* rrRotate(Node*& parent);
        Node* lrRotate(Node*& parent);
        Node* rlRotate(Node*& parent);
        
        Node* balance(Node* temp, int& ll, int& rr, int& rl, int& lr);
        void preOrderHelper(Node* parent);
        void destroy(Node* parent);
        Node* insertHelper(Node* parent, int data, bool& inserted, int& ll, int& rr, int& rl, int& lr, int& numVisited);
        bool lookupHelper(Node* node, int data, int &visitedNum);
        int getLevelHelper(Node* parent, int data, int level);
    public:
        Tree();
        bool insert(int data, int& ll, int& rr, int& rl, int& lr, int& numVisited);
        int getLevel(int data);
        bool lookup(int data, int& visitedNum);
        void preOrder();
        
        ~Tree();

};
#endif
