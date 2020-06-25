#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <algorithm>
#include "minheap.h"

using namespace std;

void printList(const vector<Node> &vector){
    for(Node v:vector){
        cout<<v.des<<","<<v.weight<<" ";
    }
    cout<<endl;
}

void printMapOfVec(const unordered_map<int,vector<Node>> &MapOfVec){
    for(int i = 1 ; i <= 9 ; i++){
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

void printL(const vector<tuple<int,int,int>> &vector){
    for(auto v:vector){
        cout<<get<0>(v)<<","<<get<1>(v)<<" "<<get<2>(v)<<endl;
    }
}


void readFile(string path, unordered_map<int, vector<Node>> &graph){
    ifstream file_in(path, ios_base::in);

    if(file_in.is_open()){
        int nodes_count,edge_count;
        file_in>>nodes_count>>edge_count;

        graph.reserve(nodes_count);

        int start_node,end_node,edge_weight;
        while(file_in >> start_node >> end_node >> edge_weight ){
            if(graph.find(start_node) == graph.end()){
                Node node(end_node,edge_weight);
                graph[start_node] = vector<Node>({node});
            }else{
                Node node(end_node,edge_weight);
                graph[start_node].emplace_back(node);
            }
            if(graph.find(end_node) == graph.end()){
                Node node(start_node,edge_weight);
                graph[end_node] = vector<Node>({node});
            }else{
                Node node(start_node,edge_weight);
                graph[end_node].emplace_back(node);
            }
        }
    }

}

unordered_set<int> getVertices(const unordered_map<int, vector<Node>> &graph){
    unordered_set<int> vertices;vertices.reserve(graph.size());
    for(const auto &pair:graph){
        vertices.emplace(pair.first);
    }
    return vertices;
}

int sumOfEdgeWeights(vector<tuple<int,int,int>> spanning_tree){
    int sum = 0;
    for(auto node:spanning_tree){
        sum += get<2>(node);
    }
    return sum;
}


int prims_mst(const unordered_map<int, vector<Node>> &graph){
    unordered_set<int> vertices = getVertices(graph);
    MinHeap Heap;
    Heap.initialize(vertices);

    int starting_vertex = *vertices.begin();
    unordered_set<int> X;
    vector<tuple<int,int,int>> spanning_tree;

    Heap.UpdateHeapAt(starting_vertex,0);
    int sum=0;

    while(!Heap.isempty()){
        pair<int,int> node = Heap.get_min();
        sum += node.second;
        X.emplace(node.first);

        for(Node endVertex: graph.at(node.first)){
            if(X.find(endVertex.des) == X.end()){
                Heap.UpdateHeapAt(endVertex.des,min(endVertex.weight,Heap.CurrentGreedyScoreOf(endVertex.des)));
            }
        }
    }

    return sum;
}


int main(){
    string path = "../prims.txt";
    unordered_map<int, vector<Node>> graph;
    readFile(path, graph);
    cout<<prims_mst(graph)<<endl;
    return 0;
}
