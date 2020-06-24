#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <tuple>


/**
 * JUST CHANGE DIVISION TO SUBTRACT IN LINE 30 FOR THE FIRST PROBLEM
 */
using namespace std;

void printVec(vector<tuple<int,int,float>> jobs){
    for(auto job:jobs){
        cout<<get<0>(job)<<" "<<get<1>(job)<<" "<<get<2>(job)<<endl;
    }
}

void readFile(string path, vector<tuple<int,int,float>> &jobs){
    ifstream file_in(path, ios_base::in);

    int totalJobs;
    file_in>>totalJobs;
    jobs.reserve(totalJobs);

    if(file_in.is_open()){
        int weight,length;
        while(file_in >> weight >> length){
            jobs.emplace_back(make_tuple(weight,length, float(weight) / length));
        }
    }
}

bool compare(tuple<int,int,float> job1, tuple<int,int,float> job2){
    if(get<2>(job1) == get<2>(job2)){
      return get<0>(job1) > get<0>(job2);
    }
    return get<2>(job1) > get<2>(job2);
}

long int jobScheduling(vector<tuple<int,int,float>> jobs){
    sort(jobs.begin(), jobs.end(), compare);
    printVec(jobs);
    // Sum of Weighted Completion Times
    int completion_time = 0;
    long int weighted_Sum = 0;
    for(int i = 0 ; i < jobs.size(); i++){
        completion_time += get<1>(jobs[i]);
        weighted_Sum += get<0>(jobs[i]) * completion_time;
    }

    return weighted_Sum;
}

int main()
{
    string path = "../jobs.txt";
    vector<tuple<int,int,float>> jobs;
    readFile(path, jobs);
    cout<<jobScheduling(jobs)<<endl;
    return 0;
}
