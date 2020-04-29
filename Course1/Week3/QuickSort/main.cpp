#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

enum class Choose { FIRST, LAST, MEDIUM, RANDOM };

void printVector(const vector<int> &vec,int left, int right){
    for(int i = left; i < right; i++){
        cout<<vec[i]<<" ";
    }
    cout<<endl;
}

int choosePivot(vector<int> &array,int left, int right, Choose choose){
    if(choose == Choose::FIRST){
//        cout<<"First"<<endl;
        return left;
    }else if(choose == Choose::LAST){
        return right - 1;
    }else if(choose == Choose::RANDOM){
        return ( (rand() % (right-left) ) + left);
    }
}

int partition(vector<int> &array, int left, int right, int pivotIndex){
    cout<<left<<" : "<<right<<endl;
//    printVector(array,left,right);
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

    // BASE CASE
    if(arrayToSort.size() <= 1){
        return;
    }

    int pivotIndex = choosePivot(arrayToSort, left, right, Choose::FIRST);
    int pivotPosition = partition(arrayToSort,left,right,pivotIndex);

    QuickSort(arrayToSort, left, max(pivotPosition-1,0));
    QuickSort(arrayToSort, pivotPosition+1, right);
}


int main()
{
    vector<int> array{1,5,3,77,2,0,-3};
    srand(time(0));
    QuickSort(array,0,array.size());
    printVector(array,0,array.size());
    return 0;
}
