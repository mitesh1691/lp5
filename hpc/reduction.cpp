#include<iostream>
#include<omp.h>
#include<cstdlib>
#include<ctime>

using namespace std;

int minval(int arr[], int n){
    int minval = arr[0];
    #pragma omp parallel for reduction(min : minval)
    for(int i = 0; i < n; i++){
        if(arr[i] < minval) minval = arr[i];
    }
    return minval;
}

int maxval(int arr[], int n){
    int maxval = arr[0];
    #pragma omp parallel for reduction(max : maxval)
    for(int i = 0; i < n; i++){
        if(arr[i] > maxval) maxval = arr[i];
    }
    return maxval;
}

int sum(int arr[], int n){
    int sum = 0;
    #pragma omp parallel for reduction(+ : sum)
    for(int i = 0; i < n; i++){
        sum += arr[i];
    }
    return sum;
}

int average(int arr[], int n){
    return (double)sum(arr, n) / n;
}

int main(){
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    int arr[n];

    // Seed the random number generator
    srand(time(0));

    // Fill the array with random numbers
    cout << "Generated array: ";
    for(int i = 0; i < n; i++) {
        arr[i] = rand() % 100; // Generating random numbers between 0 to 99
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "The minimum value is: " << minval(arr, n) << '\n';
    cout << "The maximum value is: " << maxval(arr, n) << '\n';
    cout << "The summation is: " << sum(arr, n) << '\n';
    cout << "The average is: " << average(arr, n) << '\n';
    return 0;
}


// how to run: 
// open terminal: 
// enter this:
            // g++ -o code code.cpp -fopenmp
// then this: 
            // ./code