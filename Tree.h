#ifndef TREE_H
#define TREE_H
#include <vector>
#include <utility>
using namespace std;
struct Node{
    int data;
    Node* left;
    Node* right;
};
class Tree{
    private:
        Node* root;
        int height(Node* parent) const;
        int heightDifference(Node* parent) const;
        Node* llRotate(Node*& parent);
        Node* rrRotate(Node*& parent);
        Node* lrRotate(Node*& parent);
        Node* rlRotate(Node*& parent);
        
        Node* balance(Node* temp, int& rotation);
        void preOrderHelper(Node* parent) const;
        void destroy(Node* parent);
        Node* insertHelper(Node* parent, int data, bool& inserted, int& rotation, int& numVisited);
        bool lookupHelper(Node* node, int data, int &visitedNum) const;
        int getLevelHelper(Node* parent, int data, int level) const;
    public:
        Tree();
        bool insert(int data, int& rotation, int& numVisited);
        int getLevel(int data) const;
        bool lookup(int data, int& visitedNum) const;
        void preOrder() const;
        void leafNodes(vector<int>& leafNodes);
        void leafNodesHelper(Node* root, vector<int>& leafList);
        void findRotationHelper(Node* root, vector<pair<int, int> >& ll,  vector<pair<int, int> >& lr, vector<pair<int, int> >& rl, vector<pair<int, int> >& rr, int f1, int f2, int max, int min) const;
        void findRotation(vector<pair<int, int> >& ll,  vector<pair<int, int> >& lr, vector<pair<int, int> >& rl, vector<pair<int, int> >& rr) const;

        ~Tree();

};
#endif
