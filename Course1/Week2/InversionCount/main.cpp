#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void printVector(vector<int> toPrint){
    for(int a: toPrint){
        cout<<a<<" ";
    }
    cout<<endl;
}

void readFile(string path,vector<int> &fileOut){
    ifstream file_in(path, ios_base::in);
    int a;
    while(file_in>>a){
        fileOut.emplace_back(a);
    }
}

vector<int> merge(vector<int> left, vector<int> right,long int& count){
    vector<int> merge;
    merge.resize(left.size()+right.size());

    for(int index=0,i=0,j=0 ; index < merge.size() ; index++){
        if(i < left.size() && j < right.size()){
            if(left[i] <= right[j]){
                merge[index] = left[i];i++;
            }else{
                count += left.size() - i;
                merge[index] = right[j];j++;
            }
        }else{
            if(i == left.size()){
                merge[index] = right[j];j++;
            }else{
                merge[index] = left[i];i++;
            }
        }
    }

    return merge;
}

vector<int> mergeAndCountInversion(vector<int> &arrayToSort,long int& count){
    int size = arrayToSort.size();

    if(size <= 1){
        return arrayToSort;
    }

    vector<int> left(&arrayToSort[0],&arrayToSort[size/2]);
    vector<int> right(&arrayToSort[size/2],&arrayToSort[size]);

    left = mergeAndCountInversion(left,count);
    right = mergeAndCountInversion(right,count);

    return merge(left,right,count);
}

int main()
{
    string filepath = "../IntegerArray.txt";
    vector<int> numbers;
    readFile(filepath, numbers);
    long int count = 0;

    vector<int> sortedNumbers = mergeAndCountInversion(numbers,count);

    cout<<count<<endl;
    return 0;
}
