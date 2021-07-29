//
//  CECS328_EC3.cpp
//  EC3
//
//  Created by Melissa Hazlewood on 12/16/19.
//  Copyright © 2019 Melissa Hazlewood. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <array>
#include <random>

using namespace std;

int MSS_n(int arr[], int i, int n);
int MSS_nlogn(int arr[], int i, int n);
int MSS_mid(int arr[], int i, int n);
int * generateArray(int n); //from EC2
void printArray(int arr[], int i, int n);

int main() {
    int n;
    int * arr;
    
    cout << "Please enter a positive integer array length: ";
    cin >> n;
    
    cout << "Generating " << n << "-element array..." << endl;
    arr = generateArray(n);
    cout << "Done.\n\n\tArray:" << endl;
    
    printArray(arr, 0, n);
    
    cout << "\nMSS [O(n)]: " << MSS_n(arr, 0 , n) << endl;
    cout << "MSS [O(nlogn)]: " << MSS_nlogn(arr, 0 , n) << endl;
    
    delete [] arr;
    return 0;
}


int MSS_n(int arr[], int i, int n)
{
    int MSS = 0;
    int sum = 0;
    
    for (int j = i; j < n; j++)
    {
        sum += arr[j];
        MSS = max(MSS, sum);
        if (sum < 0)
        {
            sum = 0;
        }
    }
    
    return MSS;
}

int MSS_nlogn(int arr[], int i, int n)
{
    int MSS_left;
    int MSS_right;
    int MSS_middle;
    int MSS = 0;
    
    if (n == 1)
    {
        MSS = arr[i];
    }
    else
    {
        MSS_left = MSS_nlogn(arr, i, ceil(n/2));
        MSS_right = MSS_nlogn(arr, i+ceil(n/2), n/2);
        MSS_middle = MSS_mid(arr, i, n);
        
//        cout << "left: " << MSS_left << endl;
//        cout << "right: " << MSS_right << endl;
//        cout << "mid: " << MSS_middle << endl;

        MSS = max(MSS_left, max(MSS_right, MSS_middle));
    }
    
    return MSS;
}

int MSS_mid(int arr[], int i, int n)
{
    int mid = ceil(n/2) + i; //middle if odd num elems, right-middle if even; either way it's the first elem in right subarr
    int sum = 0;
    int max_sum_left = -200; //all elems are greater than -100, so this works as a starting comparison
    int max_sum_right = -200;
    
    for (int j = mid; j > i-1; j--)
    {
//        cout << "j, arr[j] loop 1: " << j << ", " << arr[j] << endl;
        sum += arr[j];
        max_sum_left = max(max_sum_left, sum);
    }
    
    sum = 0;
    for (int j = mid+1; j < n+i; j++)
    {
//        cout << "j, arr[j] loop 2: " << j << ", " << arr[j] << endl;
        sum += arr[j];
        max_sum_right = max(max_sum_right, sum);
    }
    return max(max_sum_left, max(max_sum_right, max_sum_left + max_sum_right));
}


int * generateArray(int n) //from EC2
{
    int * arr = new int[n]; //create new pointer to the array that will be returned
//    srand(static_cast<int>(time(0))); //comment out if used elsewhere in program

    array<int,201> tempArr;
    for (int i = -100; i < 101; i++)
    {
        tempArr[i+100] = i;
    }
    
    //time-based seed generator from c++ shuffle documentation
    int seed = static_cast<int>(chrono::system_clock::now().time_since_epoch().count());
    
    shuffle(tempArr.begin(), tempArr.end(), default_random_engine(seed));
    
    copy(tempArr.begin(), tempArr.begin()+n, arr);
//    printArray(tempArr.data(), 0, 100);
    return arr;
}

void printArray(int arr[], int i, int n)
{
    cout << "\t[ ";
    for (int j = i; j < i+n-1; j++)
    {
        cout << arr[j] << ", ";
    }
    cout << arr[i + n-1] << " ]\n";
}
