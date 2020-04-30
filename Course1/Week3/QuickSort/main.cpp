#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>

using namespace std;

long int totalComparisons=0;

enum class Choose { FIRST, LAST, MEDIAN, RANDOM };

void printVector(const vector<int> &vec,int left, int right){
    for(int i = left; i < right; i++){
        cout<<vec[i]<<" ";
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

int median(vector<int> &array, int first, int last, int middle){
    if( (array[last] <= array[first] && array[first] <= array[middle])
            ||
        (array[middle] <= array[first] && array[first]  <= array[last])
    ){
        return first;
    }else if( (array[first] <= array[last] && array[last] <= array[middle])
                ||
              (array[middle] <= array[last] && array[last]  <= array[first])
           ){
        return last;
    }else{
        return middle;
    }
}

int choosePivot(vector<int> &array,int left, int right, Choose choose){
    if(choose == Choose::FIRST){
        return left;
    }else if(choose == Choose::LAST){
        return right - 1;
    }else if(choose == Choose::RANDOM){
        return ( (rand() % (right-left) ) + left);
    }else{
        int middle;
        if( (right - left)% 2 == 0 ){
            middle = ( (right - left) / 2) + left - 1;
        }else{
            middle = ( (right - left) / 2) + left;
        }
        return median(array,left,right-1,middle);

    }
}

int partition(vector<int> &array, int left, int right, int pivotIndex){
    totalComparisons += right - left - 1;
    if(pivotIndex != 0)
        swap(array[pivotIndex],array[left]);

    int pivot = array[left];
    int i = left + 1;

    for(int j = i ; j < right ; j++){
        if(array[j] < pivot){
            swap(array[j], array[i]);
            i++;
        }
    }

    swap(array[left], array[i-1]);

    return i-1;
}


void QuickSort(vector<int> &arrayToSort, int left, int right){
    if( (right - left) <= 1){
        return;
    }


    int pivotIndex = choosePivot(arrayToSort, left, right, Choose::MEDIAN);
    int pivotPosition = partition(arrayToSort,left,right,pivotIndex);

    QuickSort(arrayToSort, left, pivotPosition);
    QuickSort(arrayToSort, pivotPosition+1, right);
}


int main()
{
    string filepath = "../QuickSort.txt";
    vector<int> array;
    readFile(filepath, array);
//    srand(time(0));
    QuickSort(array,0,array.size());
//    printVector(array,0,array.size());
    cout<<totalComparisons<<endl;

    return 0;
}
