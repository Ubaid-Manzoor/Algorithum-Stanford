#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <list>
#include "minHeap.h"

using namespace std;

template <typename T>
void printVec(vector<T> vec){
    for(T s:vec){
        cout<<s<<" ";
    }
    cout<<endl;
}

void printList(const vector<Node> &vector){
    for(Node v:vector){
        cout<<v.des<<","<<v.weight<<" ";
    }
    cout<<endl;
}

void printMapOfVec(const unordered_map<int,vector<Node>> &MapOfVec){
    for(int i = 1 ; i <= 200 ; i++){
        cout<<i<<" -> ";
        auto endEdges = MapOfVec.at(i);
        printList(endEdges);
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
    if(delimeter == "," && str.size() >= 1){
        T value;
        stringstream(str) >> value;
        result.emplace_back(value);
    }else if(str.size() > 1){
        T value;
        stringstream(str) >> value;
        result.emplace_back(value);
    }

    return result;
}


void readFile(string path, unordered_map<int,vector<Node>> &graph,unordered_set<int> &vertices){
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
                Node node(endnode[0],endnode[1]);
                graph[startnode].emplace_back(node);
            }
        }
    }else{
        cout<<"Some Errors"<<endl;
    }
}

void initalizeDistance(unordered_map<int,int> &distances,const unordered_set<int> &vertices){
    for(const int vertex:vertices){
        distances[vertex] = numeric_limits<int>::max();
    }
}

void printDistance(unordered_map<int,int> &distances){
    for(int i = 1 ; i <= distances.size() ; i++){
        if(i == 7 || i == 37 || i == 59 || i == 82 || i == 99 || i == 115 || i == 133 || i == 165 || i == 188 || i == 197)
            cout<<distances.at(i)<<",";
    }
}


void dijistra(const unordered_map<int,vector<Node>> &graph, const unordered_set<int> vertices, int startVertex){
    MinHeap Heap;
    unordered_map<int,int> distances;initalizeDistance(distances,vertices);
    Heap.initialize(vertices);
    Heap.UpdateHeapAt(startVertex, 0);
    distances[startVertex] = 0;
    
    while(!Heap.isempty()){
        pair<int,int> node = Heap.get_min();
        distances[node.first] = node.second;
        
        vector<Node> verticesToChange = graph.at(node.first);
        for(Node endVertex:verticesToChange){
            if(Heap.present(endVertex.des)){
                int newScore = endVertex.weight + node.second;
                Heap.UpdateHeapAt(endVertex.des,min(newScore,Heap.CurrentGreedyScoreOf(endVertex.des)));
            }
        }
    }
    printDistance(distances);
}

int main()
{
    string path="../dijkstraData.txt";
    unordered_map<int,vector<Node>> graph;
    unordered_set<int> vertices;
    readFile(path, graph, vertices);
    dijistra(graph,vertices,1);
    return 0;
}
