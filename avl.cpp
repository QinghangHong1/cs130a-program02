#include "Tree.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

void insert(vector<string> content,Tree& t);
void lookup(vector<string> content, Tree t);
void formatResult(int visitedNum, int totalNum, int rotations);
void printRotationRange(const Tree& t, string type);
void printRotationHelper(vector<pair<int, int> > v, string type);

int main(int argc, char* argv[]){
    if(argc != 2){
        cerr << "Usage: ./" << argv[0] << " path/to/command/file.avl" << endl;
        exit(1);
    }
    ifstream ifs(argv[1]);
    if(ifs.fail()){
        cerr << "Open file failed" << endl;
        exit(1);
    }
    string line;
    Tree t;
    while(getline(ifs, line)){
        vector<string> content;
        string temp;
        istringstream stringLine(line);
        while(getline(stringLine, temp, ' ' )){
           
            content.push_back(temp);
        }
        if(content.size() >= 1){
            
            if(content[0] == "#"){
                continue;
            }else if(content[0] == "insert"){
                insert(content, t);
            }else if(content[0] == "lookup"){
                lookup(content, t);
            }else if(content[0] == "print"){
                if(content[1] == "tree"){
                    t.preOrder();
                    cout << endl;
                }else if(content[1] == "left-left"){
                    printRotationRange(t, "left-left");
                }else if(content[1] == "left-right"){
                    printRotationRange(t, "left-right");

                }else if(content[1] == "right-left"){
                    printRotationRange(t, "right-left");
                    
                }else if(content[1] == "right-right"){
                    printRotationRange(t, "right-right");
                }else{
                    cout << "cannot recognize" << endl;
                }
            }else{
                cout << "something strange" << endl;
            }
        }
        
    }
    
    return 0;
    
}

void insert(vector<string> content, Tree& t){
    int rotation = 0;
    int insertNum = 0;
    int visitNum = 0;
    for(unsigned int i = 1; i < content.size(); i++){
        if(t.insert(stoi(content[i]), rotation, visitNum)){
            insertNum ++;
        }
    }
    cout << "Added " << insertNum << " of " << content.size() - 1 << " nodes." << endl;
 
    formatResult(visitNum, content.size() - 1, rotation);
}
void lookup(vector<string> content, Tree t){
    int visitedNum = 0;
    int existNum = 0;
    vector<int> existElements;
    for(unsigned int i = 1; i < content.size(); i++){
        if(t.lookup(stoi(content[i]), visitedNum)){
            existNum ++;
            existElements.push_back(stoi(content[i]));
        }
    }
    string s = "[";
    for(unsigned int i = 0; i < existElements.size(); i++){
        if(i == 0){
            s += to_string(existElements[i]);
        }else{
            s +=  ", " + to_string(existElements[i]);
        }
    }
    s += "]";
    cout << "Found " << existNum << " of " << content.size() - 1 << " nodes: " << s << endl;
    formatResult(visitedNum, content.size() -1, 0);
}
void formatResult(int visitedNum, int totalNum, int rotations){
    cout << "Visited " << visitedNum 
        << " (" << visitedNum / double(totalNum) << ") nodes and performed " 
        << rotations << " (" << rotations / double(totalNum) << ") rotations." << endl << endl;

}
void printRotationRange(const Tree& t, string type){
    vector<pair<int, int>> ll;
    vector<pair<int, int>> lr;
    vector<pair<int, int>> rl;
    vector<pair<int, int>> rr;
    
    t.findRotation(ll, lr, rl, rr);
    
    if(type== "left-left"){
        printRotationHelper(ll, type);
    }else if(type == "left-right"){
        printRotationHelper(lr, type);
    }else if(type == "right-left"){
        printRotationHelper(rl, type);
    }else if(type == "right-right"){
        printRotationHelper(rr, type);
    }
}
void printRotationHelper(vector<pair<int, int> > v, string type){
    if(v.size() == 0){
        cout << "No inserts would cause a " << type <<  " rotation." << endl << endl;
        return;
    }
    cout << "The following inserts would cause a " << type << " rotation:" << endl;

    for(unsigned int i = 0; i < v.size(); i++){
        pair<int, int> range = v[i];
        if(i != 0){
            cout << ", ";
        }
        if(range.first == range.second){
            cout << range.first;
        }else{
            cout << range.first << " to " << range.second;
        }       
    }
    cout << endl << endl;
    
}