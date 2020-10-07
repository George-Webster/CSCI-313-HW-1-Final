//
//  main.cpp
//  Problem_5
//
//  Created by Amy Zhang on 9/26/20.
//  Copyright © 2020 Amy Zhang. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

// 5. Create a multi-level sort. For instance, for all selections of n > 10 you do sort X and within sort X, when you have a situation with n < 10 you do sort Y. Be creative. Time your sort against two “reasonably comparable” sorts (you may use libraries for the “reasonably comparable sorts”).


void InsertionSort(int arr[], int arrSize){
    // Iterate to all array's element
    for(int i = 0; i < arrSize; ++i){
        // Set the current element
        // as reference value
        int refValue = arr[i];
        
        // variable to shift the element
        // to right position
        int j;
        
        // Iterate through the sorted element
        // to insert the reference value
        // in right position
        for(j = i - 1; j >= 0; --j){
            // if the value of the current index
            // is greater than the reference value then
            // move the current value to right side
            // otherwise, put the reference value
            // in the current index
            if(arr[j] > refValue)
                arr[j+1] = arr[j];
            else
                break;
        }
        
        // here's the line to put the reference value
        // in the current index (the right position)
        arr[j + 1] = refValue;
    }
}

//quick sort
int Partition(int arr[], int startIndex, int endIndex)
{
    // Set the first item as pivot
    int pivot = arr[startIndex];
    
    // Left sublist and right sublist
    // are initially empty
    int middleIndex = startIndex;
    
    // Iterate through arr[1 ... n - 1]
    for (int i = startIndex + 1; i <= endIndex; ++i)
    {
        if (arr[i] < pivot)
        {
            // the current item is on the left sublist
            // prepare a seat by shifting middle index
            ++middleIndex;
            
            // the arr[middleIndex] is
            // the member of right sublist,
            // swap it to the current item which is
            // member of left list
            swap(arr[i], arr[middleIndex]);
        }
    }
    
    // By now, the arr[middleIndex] item is
    // member of left sublist.
    // We can swap it with the pivot
    // so the pivot will be in the correct position
    // which is between left sublist and right sublist
    swap(arr[startIndex], arr[middleIndex]);
    
    // return the index of pivot
    // to be used by next quick sort
    return middleIndex;
}

void QuickSort(int arr[], int startIndex, int endIndex , int size)
{
    // If condition is met, then do insertion sort.
    if(endIndex - startIndex < 10){
        InsertionSort(arr, size);
    }
    // Do quick sort.
    else{
        // Only perform sort process
        // if the end index is higher than start index
        if (startIndex < endIndex)
        {
            // Retrieve pivot position from Partition() function
            // This pivotIndex is the index of element that is already
            // in correct position
            int pivotIndex = Partition(arr, startIndex, endIndex);
            
            // Sort left sublist
            // arr[startIndex ... pivotIndex - 1
            QuickSort(arr, startIndex, pivotIndex - 1, size);
            
            // Sort right sublist
            // arr[pivotIndex + 1 ... endIndex]
            QuickSort(arr, pivotIndex + 1, endIndex, size);
        }
    }
}


int main() {
    srand(time(nullptr));
    // Size variable is the capacity size for array. Use random function to generate a number for size.
    int size = rand() % 20 + 1;
    // Declare a array of size (size is randomly generated).
    int array[size];
    cout << "Array size is: " << size << "\n\n";
    cout << "Unsorted array is: ";
    cout << "[ ";
    // Assign a random number for each position (from index 0 to size) of array. Will print the unsorted array with the intialized random numbers.
    for(int i = 0; i < size; i++){
        array[i] = rand() % 50 + 1;
        cout << array[i] << " ";
    }
    cout << "]\n";
    // Call QuickSort function.
    // Print the sorted array.
    QuickSort(array, 0, size - 1, size);
    cout << "\nSorted array is: [ ";
    for(int i = 0; i < size; i++){
        cout << array[i] << " ";
    }
    cout << "]";
}
