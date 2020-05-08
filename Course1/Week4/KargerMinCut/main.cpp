#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <list>
#include <time.h>

using namespace std;

struct Edge{
    int start=0,end=0;
};

/*
    HELPER FUNCTIONS
*/

void printVector(const vector<int> &vec){
    for(int v:vec){
        cout<<v<<" ";
    }
    cout<<endl;
}

void printList(const list<int> &list){
    for(int v:list){
        cout<<v<<" ";
    }
    cout<<endl;
}

void printMapOfVec(const unordered_map<int,list<int>> &MapOfVec){
    for(pair<int,list<int>> valueToVec: MapOfVec){
        cout<<valueToVec.first<<" -> ";
        printList(valueToVec.second);
    }
}



vector<int> split(string str, string delimeter=" "){
    vector<int> result;
    size_t position = str.find_first_of(delimeter);
    while(position != string::npos){
        int value;
        stringstream(str.substr(0,position)) >> value;
        result.emplace_back(value);
        str.replace(0,position+1," ");
        position = str.find_first_of(delimeter);
    }

    return result;
}

void printEdges(const vector<Edge> Edges, int limit=100){
    for(Edge edge:Edges){
        if(limit == 0){
            break;
        }
        limit--;
        cout<<"("<<edge.start<<","<<edge.end<<")"<<",";
    }
    cout<<endl;
}
/****************************************************************************************/

/*
    USED TO READ THE FILE
*/

void readFile(string path, unordered_map<int,list<int>> &graph, vector<Edge> &Edges){
    ifstream file_in(path, ios_base::in);
    string line;
    if(file_in.is_open()){
        while(getline(file_in,line)){
            vector<int> listOfNodes = split(line,"\t");
            graph[listOfNodes[0]] = list<int>(listOfNodes.begin()+1,listOfNodes.end());
            for(int i = 1; i < listOfNodes.size() ; i++){
                Edge edge;
                edge.start = listOfNodes[0];
                edge.end = listOfNodes[i];
                Edges.emplace_back(edge);
            }
        }
    }else{
        cout<<"Some Errors"<<endl;
    }
}

/****************************************************************************************/


void mergeEdge(unordered_map<int, list<int>> &graph, Edge randomEdge){
    int startNode = randomEdge.start;
    int endNode = randomEdge.end;
    list<int> listOfNodes = graph[endNode];

    /*
        First replace all node attached to endNode with startNode
        Because we have to deleted the endNode
    */
    for(int node:listOfNodes){
        list<int> &nodes = graph[node];
        replace(nodes.begin(),nodes.end(),endNode,startNode);
    }

    /*
        Stick the nodes attached with endNode to startNode in graph
    */
    list<int> &startNodes = graph[startNode];
    startNodes.splice(startNodes.end(),graph[endNode]);

    /*
        Now delete endNode in Nodes of StartNode and Loops
    */
    startNodes.remove(startNode);
    startNodes.remove(endNode);

}


Edge pickEdge(vector<Edge> &edges){
    srand(time(0));
    int edgeIndex = rand() % edges.size();
    Edge edge = edges[edgeIndex];
    edges.erase(edges.begin()+edgeIndex);
    return edge;
}

int MinCut(unordered_map<int, list<int>> &graph, vector<Edge> &Edges){
    while(Edges.size() > 2){
        Edge randomEdge = pickEdge(Edges);
//        cout<<"********************4"<<endl;
//        cout<<Edges.size();
//        cout<<"********************"<<endl;
//        cout<<"("<<randomEdge.start<<","<<randomEdge.end<<")"<<endl;
//        cout<<"********************"<<endl;
        mergeEdge(graph,randomEdge);
    }
}

int main()
{
    string path="../kargerMinCut.txt";

    unordered_map<int,list<int>> graph;
    vector<Edge> Edges;
    readFile(path,graph,Edges);
//    cout<<"Size "<<Edges.size()<<endl;
    MinCut(graph,Edges);
//    pickEdge(Edges);
    printEdges(Edges);
    printMapOfVec(graph);

    return 0;
}
