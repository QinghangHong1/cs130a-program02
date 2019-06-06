#include "Tree.h"
#include <algorithm>
#include <iostream>

using namespace std;


Tree::Tree(){
    root = 0;
}
int Tree::height(Node* parent) const{
    if(parent == NULL){
        return -1;
    }else{
        return 1 + max(height(parent -> left), height(parent -> right));
    }
}
Node* Tree::llRotate(Node*& parent){
    Node* temp = parent -> left;
    parent -> left = temp -> right;
    temp -> right = parent;
    

    return temp;
}
Node* Tree::rrRotate(Node*& parent){
    Node* temp = parent -> right;
    parent -> right = temp -> left;
    temp -> left = parent;
    

    return temp;
}
Node* Tree::lrRotate(Node*& parent){
    Node* temp = parent -> left;
    parent -> left = rrRotate(temp);
    temp = llRotate(parent);
    
    return temp;
}
Node* Tree::rlRotate(Node*& parent){
    Node* temp = parent -> right;
    parent -> right = llRotate(temp);
   

    return rrRotate(parent);
}
int Tree::heightDifference(Node* parent) const{
    //return postive if left subtree is taller, negative if right subtree is taller
    return height(parent -> left) - height(parent -> right);
}
Node* Tree::insertHelper(Node *parent, int value, bool& inserted, int& rotation, int& numVisited){
    if(parent == NULL){
        Node* newNode = new Node;
        newNode -> data = value;
        newNode -> left = 0;
        newNode -> right = 0;
        inserted = true;
        
        return newNode;
    }else if(value < parent -> data){

        numVisited ++;
        parent -> left = insertHelper(parent -> left, value, inserted, rotation, numVisited);
        parent = balance(parent, rotation);
       
    }else if(value > parent -> data){
        
        numVisited ++;
        parent -> right = insertHelper(parent -> right, value, inserted, rotation, numVisited);
        parent = balance(parent, rotation);
        
    }else{
        
        inserted = false;
    }
    return parent;
}
bool Tree::insert(int data, int& rotation, int& numVisited){
    bool inserted = false;
    root = insertHelper(root, data, inserted, rotation, numVisited);
    return inserted;
}
Node* Tree::balance(Node* temp, int& rotation){
    int heightDiff = heightDifference(temp);
    if(heightDiff > 1){
        if(heightDifference(temp -> left) > 0){
            temp = llRotate(temp);
            rotation ++;
        }else{
            temp = lrRotate(temp);
            rotation += 2;
        }
    }else if(heightDiff < -1){
        if(heightDifference(temp -> right) > 0){
            temp = rlRotate(temp);
            rotation += 2;
        }else{
            temp = rrRotate(temp);
            rotation ++;
        }
    }
    return temp;
}
bool Tree::lookupHelper(Node* node, int data, int& visitedNum) const{
    if(node == 0){
        return false;
    }else if(node -> data == data){
        visitedNum ++;
        return true;
    }else if(node -> data < data){
        visitedNum ++;
        return lookupHelper(node -> right, data, visitedNum);
    }else{
        visitedNum ++;
        return lookupHelper(node -> left, data, visitedNum);
    }
}
bool Tree::lookup(int data, int& visitedNum) const{
    return lookupHelper(root, data, visitedNum);
}
void Tree::preOrderHelper(Node* parent) const{
    if(parent != NULL){
        int level = getLevel(parent -> data);
        
        string tabs ="";
        for(int i = 1; i < level; i++){
            tabs += "  ";

        }
        cout << tabs;

        if(parent -> left == NULL && parent -> right ==NULL){
            cout << "Leaf(" << parent -> data <<  ")" << endl;
        }
        else{
            cout << "Node(" << parent -> data << ", h=" << height(parent) << "):" << endl;

            if(parent -> right == NULL){
                preOrderHelper(parent -> left);
                cout << tabs << "  Null" << endl;
            }else if(parent -> left == NULL){
                cout << tabs << "  Null" << endl;
                preOrderHelper(parent -> right);

            }else{
                preOrderHelper(parent -> left);
                preOrderHelper(parent -> right);
            }
        }
    }     
}
void Tree::preOrder() const{
    preOrderHelper(root);

}

void Tree::destroy(Node* parent){
    if (parent)
    {
        destroy(parent->left);
        destroy(parent->right);
        delete parent;
    }
}
Tree::~Tree(){
    destroy(root);
}

int Tree::getLevelHelper(Node* parent, int data, int level) const{
    if(parent==NULL){
		return 0;
    }
	if(parent->data == data){
     	return level;
    }
	int result=getLevelHelper(parent -> left, data ,level+1) ;
	if(result!=0){ 
		// If found in left subtree , return 
		return result;
	}
	result= getLevelHelper(parent -> right, data, level+1);
	return result;
}
int Tree::getLevel(int data) const{
    return getLevelHelper(root, data, 1);
}
void Tree::leafNodesHelper(Node* root, vector<int>& leafList){
    if(root == NULL){
        return;
    }
    if(root -> left == NULL && root -> right ==NULL){
        leafList.push_back(root -> data);
        return;
    }
    if(root -> left != NULL){
        leafNodesHelper(root -> left, leafList);
    }
    if(root -> right != NULL){
        leafNodesHelper(root -> right, leafList);
    }
}
void Tree::leafNodes(vector<int>& leafList){
    leafNodesHelper(root, leafList);
}
void Tree::findRotationHelper(Node* root, vector<pair<int, int> >& ll,  vector<pair<int, int> >& lr, vector<pair<int, int> >& rl, vector<pair<int, int> >& rr, int f1, int f2, int max, int min) const{
    //Precondition: the data is in one of the leaves
    if(!root){
        return;
    }
    if(root -> left != NULL || root -> right != NULL){ // non-leaf nodes
        int diff = heightDifference(root);
        if(diff == 1){//left tree is taller        left : 1    right : -1
            findRotationHelper(root -> left, ll, lr, rl, rr, 1, 0, root -> data -1, min);
            findRotationHelper(root -> right, ll, lr, rl, rr, 0 , 0, max, root -> data + 1);
        }else if(diff == -1){//right tree is taller
            findRotationHelper(root -> left, ll, lr, rl, rr, 0 , 0, root -> data -1, min);
            findRotationHelper(root -> right, ll, lr, rl, rr, -1, 0, max, root -> data + 1);
        }else if(diff == 0){
            if(f2 == 0){
                findRotationHelper(root -> left, ll, lr, rl, rr, f1, 1, root -> data - 1, min);
                findRotationHelper(root -> right, ll, lr, rl, rr, f1, -1, max, root -> data + 1);
            }

            else{
                findRotationHelper(root -> left, ll, lr, rl, rr, f1, f2, root -> data - 1, min);
                findRotationHelper(root -> right, ll, lr, rl, rr, f1, f2, max, root -> data + 1);
            }
        }
    }else{// reach the leaf node
        if(f1 == 1 && f2 == 1){
            //left-left rotation
            if((max) >= (min)){
                pair<int, int> range (min , max);
                ll.push_back(range);
            }
        }else if(f1 == 1 && f2 == -1){
            // left-right rotation
            if((max -1) >= (min + 1)){
                pair<int, int> range (min, max);
                lr.push_back(range);
            }
        }else if(f1 == -1 && f2 == 1){
            // right-left rotation
            if((max) >= (min)){
                pair<int, int> range (min, max);
                rl.push_back(range);
            }
        }else if(f1 == -1 && f2 == -1){
            // right-right rotation
            if((max ) >= (min)){
                pair<int, int> range (min, max);
                rr.push_back(range);
            }
        }else if(f1 != 0 && f2 == 0){
            // both rotations
            if(f1 == 1){
                if((min) <= (root -> data -1)){
                    pair<int, int> range (min, root -> data -1);
                    ll.push_back(range);
                }
                if((root -> data + 1) <= (max)){
                    pair<int, int> range (root -> data + 1, max);
                    lr.push_back(range);
                }
            }else if(f1 == -1){
                if((min) <= (root -> data -1)){
                    pair<int, int> range (min, root -> data - 1);
                    rl.push_back(range);
                }
                if((root -> data + 1) <= (max)){
                    pair<int, int> range (root -> data + 1, max);
                    rr.push_back(range);
                }
            }
        }
        else if(f1 == 0){
            // no rotation 
            return;
        }
    }
    // if((root -> data > data && heightDifference(root) == 1)){
    //     // left tree is taller
    //     // go to the taller tree (left)
    //     f1 = 1; // 1 : left   -1 : right
    //     f2 = 0;
    //     max = root -> data - 1;
    //     findLeafHelper(root -> left, data, ll, lr, rl, rr, f1, f2, max , min);
    // }else if((root -> data < data && heightDifference(root) == -1)){
    //     // right tree is taller
    //     // go to the taller tree (right)
    //     f1 = -1;
    //     f2 = 0;       
    //     min = root -> data + 1;
    //     findLeafHelper(root -> left, data, ll, lr, rl, rr, f1, f2, max , min);
    // }else if(root -> data < data && heightDifference(root) == 1){
    //     // left tree is taller
    //     // go to the shorter tree (right)
    //     f1 = 0;
    //     f2 = 0;
    //     min = root -> data + 1;
    //     findLeafHelper(root -> left, data, ll, lr, rl, rr, f1, f2, max , min);
    // }else if(root -> data > data && heightDifference(root) == -1){
    //     // right tree is taller
    //     // go to the shorter tree (left)
    //     f1 = 0;
    //     f2 = 0;
    //     max = root -> data - 1;
    //     findLeafHelper(root -> left, data, ll, lr, rl, rr, f1, f2, max , min);    
    // }else if(root -> data > data && heightDifference(root) == 0){
    //     // equal height difference
    //     // go to the left
    //     if(f2 == 0){
    //         f2 = 1;
    //     }
    //     max = root -> data - 1;
    //     findLeafHelper(root -> left, data, ll, lr, rl, rr, f1, f2, max , min);    
    // }else if(root -> data < data && heightDifference(root) == 0){
    //     // go to the right
    //     if(f2 == 0){
    //         f2 = -1;
    //     }
    //     min = root -> data + 1;
    //     findLeafHelper(root -> left, data, ll, lr, rl, rr, f1, f2, max , min);
    
    
}
void Tree::findRotation(vector<pair<int, int> >& ll,  vector<pair<int, int> >& lr, vector<pair<int, int> >& rl, vector<pair<int, int> >& rr) const{
    findRotationHelper(root, ll, lr, rl, rr, 0, 0, 2147483647, -2147483648);
}
