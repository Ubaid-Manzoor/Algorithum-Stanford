#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

void printVec(const vector<long int> &numbers, int limit=100){
    for(long int num: numbers){
        if(num >= 0 ){
            cout<<num<<",";
        }
    }
    cout<<endl;
}

void readFile(string path, vector<long int> &numbers){
    unordered_set<long int> bag;
    ifstream file_in(path, ios_base::in);
    if(file_in.is_open()){
        string number;
        while(file_in >> number){
            long int num;stringstream(number) >> num;
            if(bag.find(num) == bag.end()){
                numbers.emplace_back(num);
                bag.emplace(num);
            }
        }
    }else{
        cout<<"File is not Open"<<endl;
    }
}

int twoSum(vector<long int> &numbers, long int tstart=-10000, long int tend=10000){
    unordered_set<int> bag;
    sort(numbers.begin(), numbers.end());
    for(int i = 0 ; i < numbers.size() ; i++){
        long int x = numbers[i];
        int ystart_idx = lower_bound(numbers.begin() + i, numbers.end(),tstart - x) - numbers.begin();
        if(ystart_idx != numbers.size() && x+numbers[ystart_idx] <= tend){
            int yend_idx = lower_bound(numbers.begin() + i, numbers.end(),tend - x) - numbers.begin();
            if(yend_idx == numbers.size()){
                yend_idx -= 1;
            }else if(numbers[yend_idx] != tend - x){
                yend_idx -= 1;
            }

            for(int i = ystart_idx ; i <= yend_idx ; i++){
                int sum = x + numbers[i];
                if(bag.find(sum) == bag.end())
                   bag.emplace(sum);
            }
        }
    }
    return bag.size();
}

int main()
{
    string path = "../2sum.txt";
    vector<long int> numbers;
    readFile(path,numbers);
    int answer = twoSum(numbers);
    cout<<answer<<endl;
    return 0;
}
