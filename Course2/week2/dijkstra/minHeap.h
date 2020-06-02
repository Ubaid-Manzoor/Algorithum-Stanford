//
// Created by ubaid on 01/06/20.
//
#pragma once

#include<iostream>
#include<vector>
#include<unordered_map>
#include <limits>

using namespace std;

class Node{
public:
    int des;
    int weight;
    Node(int des,int weight){
        this->des=des;
        this->weight = weight;
    }
};

class MinHeap{

public:
    int Index_of(int StartVertex);
    void UpdateHeapAt(int index,int CurrentScore);
    int CurrentGreedyScoreOf(int index);
    void Print_VertexAndIndex();
    void Print_Heap();
    void initialize(const unordered_set<int>& vertices);
    void insert(int vertex,int value);
    void UpdateVertexIndex(int a,int b);
    bool present(int vertex);
    pair<int,int> get_min();
    void Print();
    bool isempty();
    void CheckIndex();

private:
    vector<pair<int,int> > Heap;
    unordered_map<int,int> Vertex_and_Index;

    bool hasParent(int);
    bool FirstChildExit(int);
    bool SecondChildExit(int);
    int FirstChildindex(int);
    int SecondChildindex(int);
    int ParentIndex(int);
    void Swap(pair<int,int>&,pair<int,int>&);
    void HeapifyUp(int);
    void HeapifyDown(int);
};



/////////////////////////   DEFINITIONS   /////////////////////////////////////////////

/// PUBLIC
bool MinHeap::present(int vertex){
    return Vertex_and_Index.find(vertex) != Vertex_and_Index.end();
}

void MinHeap::CheckIndex(){
    
    for(int i = 0 ; i < Heap.size() ; i++){
        if(i != Vertex_and_Index[Heap[i].first]){
            cout<<"Some Not Right"<<endl;
        }else{
            cout<<i<<endl;
        }
    }
    cout<<"=====================Done============================"<<endl;
}

int MinHeap::Index_of(int vertex){
    return Vertex_and_Index[vertex];
}

void MinHeap::UpdateHeapAt(int vertex,int newScore){
    Heap[MinHeap::Index_of(vertex)].second = newScore;
    HeapifyUp(MinHeap::Index_of(vertex));
}

int MinHeap::CurrentGreedyScoreOf(int vertex){
    return Heap[MinHeap::Index_of(vertex)].second;
}
void MinHeap::Print_VertexAndIndex(){
    unordered_map<int ,int >::iterator it1;
    cout<<endl;
    for(it1 = Vertex_and_Index.begin() ; it1 != Vertex_and_Index.end() ;it1++){
        cout<<it1->first<<" ";
        cout<<it1->second<<endl;
    }
}

void MinHeap::Print_Heap(){
    vector<pair<int,int> >::iterator it;
    for(it = Heap.begin() ; it != Heap.end() ; it++){
        cout<<"("<<it->first<<",";
        cout<<it->second<<")"<<" ";
        cout<<endl;
    }
    cout<<endl;
}

void MinHeap::initialize(const unordered_set<int>& vertices){
    for(const int &vertex:vertices){
        Vertex_and_Index.insert(make_pair(vertex,Heap.size()));
        Heap.push_back(make_pair(vertex,numeric_limits<int>::max()));
    }
}

void MinHeap::insert(int vertex,int value){
    pair<int,int> temp;
    temp.first = vertex;
    temp.second = value;
    Heap.push_back(temp);
    HeapifyUp(Heap.size() - 1);
}
void MinHeap::UpdateVertexIndex(int a,int b){
    Vertex_and_Index[Heap[a].first] = b;
    Vertex_and_Index[Heap[b].first] = a;
}
pair<int,int> MinHeap::get_min(){
    pair<int,int> temp;
    temp.first = Heap[0].first;
    temp.second = Heap[0].second;
    Heap[0] = Heap[Heap.size() - 1];
    Vertex_and_Index.erase(temp.first);
    Vertex_and_Index[Heap[0].first] = 0;
    Heap.pop_back();
    HeapifyDown(0);
    return temp;
}

void MinHeap::Print(){
    if(isempty()){
        cout<<endl<<"Heap is Empty"<<endl;
        return;
    }
    vector<pair<int,int> >::iterator it;
    for(it = Heap.begin() ; it != Heap.end() ; it++){
        cout<<"("<<it->first<<",";
        cout<<it->second<<")"<<" ";
    }
    cout<<endl;
}
bool MinHeap::isempty(){
    return Heap.empty();
}


/// PRIVATE

bool MinHeap::hasParent(int index){
    return ParentIndex(index) >= 0;
}
bool MinHeap::FirstChildExit(int Parentindex){
    return (Parentindex*2 + 1) < Heap.size();
}
bool MinHeap::SecondChildExit(int Parentindex){
    return (Parentindex*2 + 2) < Heap.size();
}
int MinHeap::FirstChildindex(int Parentindex){
    return Parentindex*2 + 1;
}
int MinHeap::SecondChildindex(int Parentindex){
    return Parentindex*2 + 2;
}
int MinHeap::ParentIndex(int index){
    return (index-1)/2;
}
void MinHeap::Swap(pair<int,int>& a , pair<int,int>& b){
    UpdateVertexIndex(Vertex_and_Index[a.first],Vertex_and_Index[b.first]);
    pair<int,int> c;
    c = a;
    a = b;
    b = c;
}
void MinHeap::HeapifyUp(int index){
    while(hasParent(index) && Heap[ParentIndex(index)].second > Heap[index].second){
        Swap(Heap[ParentIndex(index)],Heap[index]);
        index = ParentIndex(index);
    }
}
void MinHeap::HeapifyDown(int index){
    while(FirstChildExit(index)){
        int SmallChildIndex = FirstChildindex(index);
        if(Heap[SecondChildindex(index)].second < Heap[FirstChildindex(index)].second){
            SmallChildIndex = SecondChildindex(index);
        }
        if(Heap[index].second < Heap[SmallChildIndex].second){
            break;
        }else{
            Swap(Heap[SmallChildIndex],Heap[index]);
        }
        index = SmallChildIndex;
    }
}