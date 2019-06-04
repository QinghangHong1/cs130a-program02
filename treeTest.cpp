//treeTest.cpp
#include "Tree.h"
#include <iostream>
using namespace std;

int main(){
    Tree t;
    assert(t.insert(10));
    assert(!t.insert(10));
    assert(t.insert(20));
    assert(t.insert(40));
    assert(!t.insert(10));
    assert(t.insert(25));
    assert(t.lookup(10));
    assert(t.lookup(40));
    assert(t.lookup(20));

    cout << "all tests passed" << endl;
}