#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

void printHeap(vector<int> heap){
    for(int value:heap){
        cout<<value<<" ";
    }
    cout<<endl;
}


void balanceHeaps(vector<int> &lowHeap,vector<int> &highHeap){
    int front;
    if(lowHeap.size() > highHeap.size()){
        front = lowHeap.front();
        pop_heap(lowHeap.begin(), lowHeap.end());
        lowHeap.pop_back();

        highHeap.emplace_back(front);
        push_heap(highHeap.begin(), highHeap.end(),greater<int>{});
    }else{
        front = highHeap.front();
        pop_heap(highHeap.begin(), highHeap.end(),greater<int>{});
        highHeap.pop_back();

        lowHeap.emplace_back(front);
        push_heap(lowHeap.begin(), lowHeap.end());
    }
}

int Median(vector<int> &lowHeap, vector<int> &highHeap,int newValue){
    if(lowHeap.size() == 0){
        lowHeap.emplace_back(newValue);
        push_heap(lowHeap.begin(), lowHeap.end());
    }else if(newValue < lowHeap[0]){
        lowHeap.emplace_back(newValue);
        push_heap(lowHeap.begin(), lowHeap.end());
    }else if(newValue > lowHeap[0]){
        highHeap.emplace_back(newValue);
        push_heap(highHeap.begin(), highHeap.end(),greater<int>{});
    }

    // BALANCE BOTH HEAP
    if(abs(int(lowHeap.size() - highHeap.size())) > 1){
        balanceHeaps(lowHeap,highHeap);
    }

    if( (lowHeap.size() + highHeap.size()) % 2 == 0 ){
        return lowHeap.front();
    }else{
        if(lowHeap.size() > highHeap.size()){
            return lowHeap.front();
        }else{
            return highHeap.front();
        }
    }
}

int MedianMaintenance(string path){
    vector<int> lowHeap,highHeap;
    make_heap(lowHeap.begin(),lowHeap.end());
    make_heap(highHeap.begin(),highHeap.end(), greater<int>{});

    int Sum=0;

    ifstream file_in(path,ios_base::in);
    int value;
    while(file_in >> value){
        int median = Median(lowHeap,highHeap,value);
        Sum += median;
    }

    return Sum;
}

int main()
{
    string path="../Median.txt";
    int result = MedianMaintenance(path);
    cout<<"RESULT :: "<<result<<endl;
    return 0;
}
