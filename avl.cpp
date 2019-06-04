#include "Tree.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

void insert(vector<string> content,Tree& t);
void lookup(vector<string> content, Tree& t);
void formatResult(int visitedNum, int totalNum, int rotations);


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
                }else if(content[1] == "left-left"){

                }else if(content[1] == "left-right"){
                    
                }else if(content[1] == "right-left"){
                    
                }else if(content[1] == "right-right"){
                    
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
    int ll = 0;
    int rr = 0;
    int rl = 0;
    int lr = 0;
    int insertNum = 0;
    int visitNum = 0;
    for(unsigned int i = 1; i < content.size(); i++){
        if(t.insert(stoi(content[i]), ll, rr, rl, lr, visitNum)){
            insertNum ++;
        }
    }
    int totalRotation = ll + rr + 2 * rl + 2 * lr;
    cout << "Added " << insertNum << " of " << content.size() - 1 << " nodes." << endl;
 
    formatResult(visitNum, content.size() - 1, totalRotation);
}
void lookup(vector<string> content, Tree &t){
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
    cout << "visited " << visitedNum 
        << " (" << visitedNum / double(totalNum) << ") nodes and performed " 
        << rotations << " (" << rotations / double(totalNum) << ") rotations." << endl;

}