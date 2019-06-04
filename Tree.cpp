#include "Tree.h"
#include <algorithm>
#include <iostream>
using namespace std;


Tree::Tree(){
    root = 0;
}
int Tree::height(Node* parent){
    if(parent == NULL){
        return 0;
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
int Tree::heightDifference(Node* parent){
    //return postive if left subtree is taller, negative if right subtree is taller
    return height(parent -> left) - height(parent -> right);
}
Node* Tree::insertHelper(Node *parent, int value, bool& inserted, int& ll, int& rr, int& rl, int& lr, int& numVisited){
    if(parent == NULL){
        Node* newNode = new Node;
        newNode -> data = value;
        newNode -> left = 0;
        newNode -> right = 0;
        inserted = true;
        return newNode;
    }else if(value < parent -> data){
        numVisited ++;
        parent -> left = insertHelper(parent -> left, value, inserted, ll, rr, rl, lr, numVisited);
        parent = balance(parent, ll, rr, rl, lr);
       
    }else if(value > parent -> data){
        numVisited ++;
        parent -> right = insertHelper(parent -> right, value, inserted, ll, rr, rl, lr, numVisited);
        parent = balance(parent, ll, rr, rl, lr);
        
    }else{
        inserted = false;
    }
    return parent;

}
// Node* Tree::remove(Node* parent, int data){
//     if(parent == NULL){
//         return parent;
//     }
//     if(data < parent -> data){
//         remove(parent -> left, data);
//     }else if(data > parent -> data){
//         remove(parent -> right, data);
//     }else if(parent -> right == NULL && parent -> left ==NULL){
//         delete parent;
//         parent = NULL;
//     }else if(parent -> left == NULL){
//         Node* temp = parent -> right;
//         *parent = *temp;
//         delete temp;

//     }else if(parent -> right == NULL){
//         Node* temp = parent -> left;
//         *parent = *temp;
//         delete temp;
//     }
//     balance(parent);
// }
Node* Tree::balance(Node* temp, int& ll, int& rr, int& rl, int& lr){
    int heightDiff = heightDifference(temp);
    if(heightDiff > 1){
        if(heightDifference(temp -> left) > 0){
            temp = llRotate(temp);
            ll ++;
        }else{
            temp = lrRotate(temp);
            lr ++;
        }
    }else if(heightDiff < -1){
        if(heightDifference(temp -> right) > 0){
            temp = rlRotate(temp);
            rl ++;
        }else{
            temp = rrRotate(temp);
            rr ++;
        }
    }
    return temp;
}
bool Tree::lookupHelper(Node* node, int data, int& visitedNum){
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
bool Tree::lookup(int data, int& visitedNum){
    return lookupHelper(root, data, visitedNum);
}
void Tree::preOrderHelper(Node* parent){
    if(parent != NULL){
        int level = getLevel(parent -> data);
        string tabs ="";
        for(int i = 1; i < level; i++){
            tabs += "   ";
        }
        cout << tabs;

        if(parent -> left == NULL && parent -> right ==NULL){
            cout << "Leaf(" << parent -> data <<  ")" << endl;
        }
        else{
            cout << "Node(" << parent -> data << ", h=" << height(parent) - 1 << "):" << endl;

            if(parent -> right == NULL){
                preOrderHelper(parent -> left);
                cout << tabs << "   " << "Null" << endl;
            }else if(parent -> left == NULL){
                cout << "   Null" << endl;
                preOrderHelper(parent -> right);

            }else{
                preOrderHelper(parent -> left);
                preOrderHelper(parent -> right);
            }
        }
    }     
}
void Tree::preOrder(){
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
bool Tree::insert(int data, int& ll, int& rr, int& rl, int& lr, int& numVisited){
    bool inserted = false;
    root = insertHelper(root, data, inserted, ll, rr, rl, lr, numVisited);
    return inserted;
}
int Tree::getLevelHelper(Node* parent, int data, int level){
    if(parent==NULL){
        
		return 0;
    }
	if(parent->data == data){
        
     	return level;
    }
	int result=getLevelHelper(parent -> left, data ,level+1) ;
		if(result!=0)
		{ 
			// If found in left subtree , return 
			return result;
		}
	result= getLevelHelper(parent -> right, data, level+1);
	return result;
}
int Tree::getLevel(int data){
    return getLevelHelper(root, data, 1);
}
