#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <fstream>

using namespace std;

void printList(const list<int> &list){
    for(int v:list){
        cout<<v<<" ";
    }
    cout<<endl;
}

void printMapOfList(const unordered_map<int,list<int>> &MapOfVec, int limit=100){
    int lim = 0;
    for(pair<int,list<int>> valueToVec: MapOfVec){
        cout<<valueToVec.first<<" -> ";
        printList(valueToVec.second);
        lim++;
        if(lim == limit){
            break;
        }
    }
}

void printMap(const unordered_map<int,int> map){
    for(pair<int,int> p:map){
        cout<<p.first<<"->"<<p.second<<endl;
    }
}

void printComponents(const unordered_map<int,unordered_set<int>> Components){
    for(pair<int,unordered_set<int>> component:Components){
        cout<<"COMPONENT SIZE "<<component.second.size()<<endl;
        for(int vertex:component.second){
            cout<<vertex<<",";
        }
        cout<<endl;
    }
}

int stop = 0 ;

void readFile(string path, unordered_map<int, list<int>> &graph, unordered_map<int, list<int>> &reverseGraph){
    ifstream file_in(path, ios_base::in);
    if(file_in.is_open()){
        int tail, head;
        while(file_in >> tail >> head){
            if(graph.find(head) == graph.end())
                graph[head] = list<int>();
            if(reverseGraph.find(tail) == reverseGraph.end())
                reverseGraph[tail] = list<int>();

            if(graph.find(tail) == graph.end()){
                graph[tail] = list<int>(1,head);
            }else{
                graph[tail].emplace_back(head);
            }

            if(reverseGraph.find(head) == reverseGraph.end()){
                reverseGraph[head] = list<int>(1,tail);
            }else{
                reverseGraph[head].emplace_back(tail);
            }

        }
    }else{
        cout<<"Some Error"<<endl;
    }
}

namespace{
    int tim=-1;
    int leader=NULL;
    unordered_set<int> explored;
    unordered_map<int,int> finishingTime;
    unordered_map<int,unordered_set<int>> Components;
    bool reverseDFS = true;
}

int count;

void DFS(const unordered_map<int, list<int>> &graph, int vertex){
    explored.emplace(vertex);

    if(graph.find(vertex) != graph.end()){
        for(const int &headVertex:graph.at(vertex)){
            if(explored.find(headVertex) == explored.end()){
                DFS(graph, headVertex);
            }
        }
    }
    if(reverseDFS){
        tim++;

        if(tim == 0){
            cout<<"VERTEX :  "<<vertex<<endl;
        }
        finishingTime[tim] = vertex;
    }else{
        Components[leader].emplace(vertex);
    }
}


void DFS_Loop(const unordered_map<int, list<int>> &graph){
    if(!reverseDFS){
        count++;
        cout<<count<<endl;
    }
    for(int i = graph.size(); i > 0 ; i--){
        if(!reverseDFS){
            i = finishingTime[i];
        }
        if(explored.find(i) == explored.end()){
            leader = i;
            if(!reverseDFS)
                Components[leader] = (unordered_set<int>());
            DFS(graph, i);
        }
    }
}

void searchSCC(const unordered_map<int,list<int>> &graph, const unordered_map<int, list<int>> &reverseGraph){
    reverseDFS = true;
    DFS_Loop(reverseGraph);

    cout<<"First Done"<<endl;

    explored.clear();

    reverseDFS = false;
    printMap(finishingTime);
    count=0;
    DFS_Loop(graph);

    cout<<"Second Done"<<endl;
}


int main()
{
//    string path = "../smallSCC1.txt";
    string path = "../SCC.txt";
    unordered_map<int, list<int>> graph;
    unordered_map<int, list<int>> reverseGraph;
    readFile(path, graph, reverseGraph);
    printMapOfList(graph);
    cout<<"===================="<<endl;
    printMapOfList(reverseGraph);
//    cout<<"GRAPG SIZE : "<<graph.size()<<endl;
//    cout<<"REVERSE SIZE : "<<reverseGraph.size()<<endl;;
//    cout<<"READING DONE"<<endl;
    searchSCC(graph,reverseGraph);
//    cout<<"SIZE : "<<finishingTime.size()<<endl;
//    printMap(finishingTime);
    cout<<"Com Size : "<<Components.size()<<endl;
    printComponents(Components);
    return 0;
}