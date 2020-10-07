#include <iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

int* TwoDtoOneD(int** arr, int len) { //converts array from 2D to 1D
    int* myarray = new int[len];
    for (int i = 0; i < len; i++) {
        myarray[i] = *(*arr + i);
    }
    return myarray;
}

void swap(int& a, int& b) //exchange two variables
{
    int temp = a;
    a = b;
    b = temp;
}

void bubble_sort(int **arr, int arrSize) { //compares adjacent elements and swaps if they are in the wrong order
    int len = arrSize * arrSize;
    int* myarray = TwoDtoOneD(arr, len);
    int temp;
    for (int i = 0; i < len - 1; i++)
        for (int j = 0; j < len - 1 - i; j++)
            if (myarray[j] > myarray[j + 1]) {
                swap(myarray[j], myarray[j + 1]);
            }
    for (int i = 0; i < len; i++) {
        *(*arr + i) = myarray[i];
    }
}


void SelectionSort(int **arr, int arrSize) // finds the smallest element and moves it to the front, and continues to do that for subsections of the array until it is finished
{
    int len = arrSize * arrSize;
    int* myarray = TwoDtoOneD(arr, len);
    int minIndex;
    
    for (int i = 0; i < len - 1; ++i)
    {
        minIndex = i;
        for (int j = i + 1; j < len; ++j)
        {
            if (myarray[j] < myarray[minIndex])
                minIndex = j;
        }
        swap(myarray[i], myarray[minIndex]);
    }
    for (int i = 0; i < len; i++) {
        *(*arr + i) = myarray[i];
    }
}



void InsertionSort(int **arr, int arrSize) //compares each element in the array and shifts larger values over to fit smaller values towards the beginning of the array
{
    int len = arrSize * arrSize;
    int* myarray = TwoDtoOneD(arr, len);
    for (int i = 0; i < len; ++i)
    {
        int refValue = myarray[i];
        int j;
        for (j = i - 1; j >= 0; --j)
        {
            if (myarray[j] > refValue)
                myarray[j + 1] = myarray[j];
            else
                break;
        }
        myarray[j + 1] = refValue;
    }
    for (int i = 0; i < len; i++) {
        *(*arr + i) = myarray[i];
    }
}


void insertion_sort(int arr[], int len) {
    int i, j, key;
    for (i = 1; i < len; i++) {
        key = arr[i];
        j = i - 1;
        while ((j >= 0) && (arr[j] > key)) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
int main() {
    // establishes an array
    int*( myArray[5]);
    int a[5][5]= {
        { 82, 90, 91, 78, 99 },
        { 68, 72, 64, 54, 100 },
        { 95, 91, 89, 92, 97  },
        { 67, 52, 60, 55, 63},
        { 79, 81, 85, 96, 98 },
    };
    for (int i = 0; i < 5; i++) {
        myArray[i] = a[i];
    }
    // Print the unsorted array.
    cout << "The unsorted 2D array is: " << endl << endl;;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            cout << myArray[i][j] << " ";
        }
        cout << endl;
    }
    //does each type of sort on the array we created
    bubble_sort(myArray , 5);
    SelectionSort(myArray, 5);
    InsertionSort(myArray, 5);
    cout << endl;
    // Print the sorted array.
    cout << "The sorted 2D array is: " << endl << endl;
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
} 
