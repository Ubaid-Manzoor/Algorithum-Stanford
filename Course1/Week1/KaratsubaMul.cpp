//============================================================================
// Name        : KaratsubaMul.cpp
// Author      : Ubaid Manzoor
// Version     : 1.0
// Copyright   : Copyright 2020. You can use this code however and wherever you want no strings attached
// Description : C++ Functions to Perform Karatsbuba Multiplications For Big Positive Number
//============================================================================

#include <iostream>
#include <string>
#include <sstream>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::stringstream;
using std::to_string;

string append_to_start(int length, string rhs){
    string zeros(length, '0');
    return zeros.append(rhs);
}

string add(string a, string b){
    unsigned int size_of_a = a.length();
    unsigned int size_of_b = b.length();
    unsigned int size_diff = abs(size_of_a - size_of_b);
    string result;
    if(size_of_a > size_of_b){
        /* Append Zero to the start of b */
        b = append_to_start(size_diff, b);
        size_of_b = size_of_a;
    }else{
        /* Append Zero to the start of a */
        a = append_to_start(size_diff, a);
        size_of_a = size_of_b;
    }

//    cout<<a<<" : "<<b<<endl;
    /* Now Start Adding  */
    int carry = 0;
    for(int i = size_of_a-1 ; i >= 0 ; --i ){
        /*
         * a[i] or b[i] converted to int will will give asscii value
         * To get the actual value we have subtract it with '0'
         * */
        int num1 = a[i]- '0';
        int num2 = b[i] - '0';
        int sum = num1 + num2 + carry;

//        cout<<"num1 : "<<num1 << " num2 : "<<num2<<endl;
//        cout<<"sum : "<<sum<<" carry : "<<carry<<endl;
        if( sum <= 9 ){
            result.insert(0, to_string(sum) );
            carry = 0;
        }else{
            result.insert(0, to_string(sum % 10) );
            carry = 1;
        }
    }
    return result;
}

/*
 * sub is only used once and there left value is always greater
 *
 * Assumption : a >= b always
 * */
string sub(string a, string b){
    unsigned int size_of_a = a.length();
    unsigned int size_of_b = b.length();
    unsigned int size_diff = abs(size_of_a - size_of_b);

    string result;
    /* Append Zero to the start of b */
    b = append_to_start(size_diff, b);

//    cout<<a<<" : "<<b<<endl;
    /* Now Start Subtracting  */
    int borrow = 0;
    for(int i = size_of_a-1 ; i >= 0 ; --i ){
        /*
         * a[i] or b[i] converted to int will will give asscii value
         * To get the actual value we have subtract it with '0'
         * */
        int num1 = a[i] - '0';
        int num2 = b[i] - '0';
        int sub;

//        cout<<"1 : "<<num1<<" , 2 : "<<num2<<endl;

        if( (num1 < num2) || ( (num1 == num2) && borrow ) ){
            sub = (10 + num1 - borrow) - num2;
//            cout<<"sub : "<<sub<<endl;
            borrow = 1;
        }else{
            sub = num1 - borrow - num2;
            borrow = 0;
        }
        result.insert(0, to_string(sub) );
    }

    /* Removing Leading Zeros */
    while(result[0] == '0'){
        result.erase(0,1);
    }

    return result;
}


string karatsubaMultiply(string num1, string num2){

    /* Base Case */
    if(num1.length() <= 1 && num2.length() <=1){
        return to_string(  (num1[0] - '0') * (num2[0]-'0') );
    }

    /* Prepossessing */

    if(num1.length() < num2.length()){
        append_to_start(num2.length() - num1.length(), num1);
    }else{
        append_to_start(num1.length() - num2.length(), num2);
    }

    unsigned int mid_of_num1 = num1.length()/2;
    unsigned int mid_of_num2 = num2.length()/2;

    string a = num1.substr(0,mid_of_num1);
    string b = num1.substr(mid_of_num1, num1.size()-mid_of_num1);
    string c = num2.substr(0,mid_of_num2);
    string d = num2.substr(mid_of_num2, num2.size()-mid_of_num2);

    cout<<"a : "<<a<<",b : "<<b<<endl;
    cout<<"c : "<<c<<",d : "<<d<<endl;


    /* Recursion Calls */
    // STEP 1
    string ac = karatsubaMultiply(a,c); // --> 1
    // STEP 2
    string bd = karatsubaMultiply(b, d); // --> 2

    // STEP 3
    string ab_mul_cd = karatsubaMultiply(add(a,b),add(c,d)); // -->3

    /*
     * What to do is Sub 1 and 2 from 3 to get ad + bc
     * ad + bc = ( 3 ) - ( 2 ) - ( 1 ) Or ( 3 ) - ( 2  +  1 )
     * */
    /* Adding first and second equation */

    // STEP 4
    string ad_plus_bc = sub(ab_mul_cd,add(ac,bd)); // --> 4

    // LAST STEP

    /* PADD WITH ZEROS*/
    /*
     * length of b and d is same ,
     * we can have simplified it but it might give some idea
     * what actually we are padding
     * */
    ac.append(b.length() + d.length(), '0');
    ad_plus_bc.append( std::max( b.length(),d.length()) , '0' );

    return add(add(ac,ad_plus_bc),bd);
}

void testAdd(int limit){
    int fails = 0;
    for(int i = 0 ; i < limit ; ++i){
        for(int j = 0 ; j < limit ; ++j){
            if( to_string(i + j) != add( to_string(i), to_string(j) ) ){
                cout<<i<<", "<<j<<" == "<<(i+j)<<" return : "<<add(to_string(i), to_string(j))<<endl;
                fails += 1;
            }else{
                cout<<i<<", "<<j<<" == "<<(i+j)<<" return : "<<add(to_string(i), to_string(j))<<endl;
            }
        }
    }
    cout<<fails<<endl;
}


void testSub(int limit){
    int fails = 0;
    for(int i = 5999 ; i <= 5999 ; ++i){
        for(int j = 0 ; j < limit ; ++j){
            if( to_string(i - j) != sub( to_string(i), to_string(j) ) ){
                cout<<i<<", "<<j<<" == "<<(i-j)<<" return : "<<sub(to_string(i), to_string(j))<<endl;
                fails += 1;
            }else{
                cout<<i<<", "<<j<<" == "<<(i-j)<<" return : "<<sub(to_string(i), to_string(j))<<endl;
            }
        }
    }
    cout<<fails<<endl;
}

int main(){
//    string num1{},num2{};
//    num1 = "1";
//    num2 = "2718281828459045235360287471352662497757247093699959574966967627";
//    string result = karatsubaMultiply(num1,num2);
//    cout<<"Result : "<<result<<endl;
      testAdd(10);
//        testSub(5998);
//    cout<<to_string(10)<<endl;
    return 0;
}


/*
 * Problem is with add
 * check 1 + 9 ??
 *
 * */