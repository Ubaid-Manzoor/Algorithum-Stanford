//
// Created by ubaid on 15/04/20.
//
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::cin;
using std::string;

string padd(string a, int length){

}

string add(string a, string b){
    return "23";
}

string sub(string a, string b){

}

string multiply(string a, string b){

}

string karatsubaMultiply(string num1, string num2){
    /* Prepossessing */
    unsigned int mid_of_num1 = num1.length()/2;
    unsigned int mid_of_num2 = num2.length()/2;

    string a = num1.substr(0,mid_of_num1);
    string b = num1.substr(mid_of_num1, num1.size()-mid_of_num1);
    string c = num2.substr(0,mid_of_num2);
    string d = num2.substr(mid_of_num2, num2.size()-mid_of_num2);

    cout<<"a : "<<a<<",b : "<<b<<endl;
    cout<<"c : "<<c<<",d : "<<d<<endl;

    /* Base Case */
    if(a.length() <= 1 || b.length() <=1){
        return multiply(a,b);
    }

    /* Recursion Calls */

    string a_mul_b = karatsubaMultiply(a,c);
    string b_mul_d = karatsubaMultiply(b, d);

    // STEP 1
    string ac = add(a,c); // --> 1
    // STEP 2
    string bd = add(b, d); // --> 2

    // STEP 3
    string ab_mul_cd = karatsubaMultiply(add(a,b),add(c,d)); // -->3

    /*
     * What to do is Sub 1 and 2 from 3 to get ad + bc
     * ad + bc = ( 3 ) - ( 2 ) - ( 1 ) Or ( 3 ) - ( 2  +  1 )
     * */
    /* Adding first and second equation */

    // STEP 4
    string ad_plus_bc = sub(ab_mul_cd,add(ac,bd));

    // LAST STEP
    string padded_ac = padd(ac,b.length() + d.length());
    string padded_ad_plus_db = padd(ad_plus_bc,b.length() > d.length() ? b.length() : d.length());

    string result = add(add(padded_ac,padded_ad_plus_db),bd);
}

int main(){
    string num1{},num2{};
    num1 = "101400";
    num2 = "30200";
    string ac = karatsubaMultiply(num1,num2);
    return 0;
}