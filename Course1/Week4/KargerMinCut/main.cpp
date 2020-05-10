#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <list>
#include <time.h>
#include <limits>
#include <random>

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

void printEdges(const vector<Edge> Edges, int limit=250){
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

void replaceEdge(vector<Edge> &Edges,char toCheck, int toReplace, int replaceWith){
    for(Edge &edge:Edges){
        if(toCheck == 'l'){
            if(edge.start == toReplace){
                edge.start = replaceWith;
            }
        }if(toCheck == 'r'){
            if(edge.end == toReplace){
                edge.end = replaceWith;
            }
        }
    }
}

void removeEdge(vector<Edge> &Edges, Edge edge){
    int start = edge.start;
    int end = edge.end;
    for(int i = 0 ; i < Edges.size() ; i++){
        Edge edge = Edges[i];
        if( (edge.start == start && edge.end == end) || (edge.end == start && edge.start == end)){
            Edges.erase(Edges.begin() + i);
            i--;
        }
    }
}

void removeLoop(vector<Edge> &Edges, int vertex){
    Edge loop;
    loop.start = loop.end = vertex;
    removeEdge(Edges, loop);
}

void mergeEdge(unordered_map<int, list<int>> &graph, Edge randomEdge, vector<Edge> &Edges){
    int startNode = randomEdge.start;
    int endNode = randomEdge.end;
    list<int> listOfNodes = graph[endNode]; // LIST OF VERTICES ATTACHED TO END NODE

    /*
     * STEP 1:
     * Detach all node attached to endNode and attach them to startNode
     *  Because we have to deleted the endNode
    */
    for(int node:listOfNodes){
        list<int> &nodes = graph[node];
        replace(nodes.begin(),nodes.end(),endNode,startNode);
    }


    replaceEdge(Edges,'r',endNode,startNode);

    /*
     * STEP 2:
     * Stick the nodes attached with endNode to startNode in graph
    */
    list<int> &startNodes = graph[startNode];
    startNodes.splice(startNodes.end(),graph[endNode]);

    replaceEdge(Edges, 'l', endNode, startNode);
    graph.erase(endNode);

    /*
     * STEP 3:
     * Now delete endNode from the nodes attached to StartNode and also Loops
    */

    startNodes.remove(startNode); // LOOPS
    startNodes.remove(endNode); // DELETE ENDNODE
    removeLoop(Edges, startNode);
}

int seed = 0;

Edge pickEdge(vector<Edge> &edges){
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0,edges.size()-1);

    return edges[dist(mt)];
}

int MinCut(unordered_map<int, list<int>> graph, vector<Edge> Edges){
    while(graph.size() > 2){
        Edge randomEdge = pickEdge(Edges);
        removeEdge(Edges, randomEdge);
        mergeEdge(graph,randomEdge, Edges);
    }

    for(pair<int,list<int>> cutEdges: graph){
        return cutEdges.second.size();
    }
}


int main()
{
//    string path="../mincut.txt";
    string path="../kargerMinCut.txt";
    unordered_map<int,list<int>> graph;
    vector<Edge> Edges;
    readFile(path,graph,Edges);

    int minCut = numeric_limits<int>::max();

    for(int i = 0 ; i < 1000 ; i++){
        int currentCut = MinCut(graph,Edges) ;
        cout<<"CUT : "<<currentCut<<endl;
        if(currentCut < minCut){
            minCut = currentCut;
        }
    }

    cout<<"MINCUT :"<<minCut<<endl;

    return 0;
}
