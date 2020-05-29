#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <list>


using namespace std;

template <typename T>
void printVec(vector<T> vec){
    for(T s:vec){
        cout<<s<<" ";
    }
    cout<<endl;
}

void printList(const list<pair<int,int>> &list){
    for(pair<int,int> v:list){
        cout<<v.first<<","<<v.second<<" ";
    }
    cout<<endl;
}

void printMapOfVec(const unordered_map<int,list<pair<int,int>>> &MapOfVec){
    for(pair<int,list<pair<int,int>>> valueToVec: MapOfVec){
        cout<<valueToVec.first<<" -> ";
        printList(valueToVec.second);
    }
}

void printSet(const unordered_set<int> set){
    for(int vertice:set){
        cout<<vertice<<" ";
    }
    cout<<endl;
}

template <typename T>
vector<T> split(string str, string delimeter=" "){
    vector<T> result;
    size_t position = str.find_first_of(delimeter);
    while(position != string::npos){
        T value;
        stringstream(str.substr(0,position)) >> value;
        result.emplace_back(value);
        str.replace(0,position+1,"");
        position = str.find_first_of(delimeter);
    }

    if(str.size() > 1){
        T value;
        stringstream(str) >> value;
        result.emplace_back(value);
    }

    return result;
}


void readFile(string path, unordered_map<int,list<pair<int,int>>> &graph,unordered_set<int> &vertices){
    ifstream file_in(path, ios_base::in);
    string line;
    if(file_in.is_open()){
        while(getline(file_in,line)){
            vector<string> listOfNodes = split<string>(line,"\t");
            int startnode;
            stringstream(listOfNodes[0]) >> startnode;
            vertices.emplace(startnode);
            for(int i = 1 ; i < listOfNodes.size() ; i++){
                vector<int> endnode = split<int>(listOfNodes[i],",");
                graph[startnode].emplace_back(make_pair(endnode[0],endnode[1]));
            }
        }
    }else{
        cout<<"Some Errors"<<endl;
    }
}

void dijistra(const unordered_map<int,list<pair<int,int>>> &graph){

}

int main()
{
    string path="../dijkstraData.txt";
    unordered_map<int,list<pair<int,int>>> graph;
    unordered_set<int> vertices;
    readFile(path, graph, vertices);
    printSet(vertices);
//    printMapOfVec(graph);
    return 0;
}





//I completed Divide and Conquer, Sorting and Searching, and Randomized Algorithms on Coursera! Check out my certificate: https://coursera.org/share/6942bd4a4e0539474f139763c45035f2
