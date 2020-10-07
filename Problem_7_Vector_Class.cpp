//
//  main.cpp
//  Project_313
//
//  Created by Amy Zhang on 9/19/20.
//  Copyright � 2020 Amy Zhang. All rights reserved.
//


#include <iostream>
#include<ctime>
#include<cstdlib>
#include <chrono>
#include<vector>
using std::chrono::system_clock;
using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::milliseconds;
using namespace std;

// 7. Create your own vector and list. Time it similar to question #1
// Vector is faster for all part a, b, and c timings.


// Declare a template vector class.
template<typename T>
class Vector {
private:
    // Declaration of field variables
    int Size; // Track the amount of elements(length) of vector. Will increase everytime a value is added (push_back) into the vector.
    int maxSize; // The max capacity of the vector.
    T* Array; // Array pointer
    
public:
    // Default constructor
    Vector() {
        this -> Size = 0;
        this -> maxSize = 10;
        this -> Array = new T[10];
    }
    
    // Regular 1 parameter constructor
    Vector(int vectorSize) {
        Size = 0;
        this -> maxSize = vectorSize;
        Array = new T[maxSize];
    }
    
    // Regular 2 parameter constructor
    // For example: create vector(10,5) -> create a vector of integers of size ten, all initialized to 5.
    Vector(int vectorSize, T value) {
        this -> Size = vectorSize;
        this -> maxSize = vectorSize;
        this -> Array = new T[maxSize];
        // Assign each value to array.
        for (int i = 0; i < Size; i++) {
            Array[i] = value;
        }
    }
    
    // Copy constructor
    Vector(const Vector<T>& vectorObj) {
        this -> Size = vectorObj.Size;
        this -> maxSize = vectorObj.maxSize;
        Array = new T[maxSize]; // Reset the size
        
        for (int i = 0; i < vectorObj.Size; i++) {
            Array[i] = vectorObj.Array[i];
        }
    }
    // Move constructor
    Vector(Vector<T>&& vectorObj) {
        this -> Size = vectorObj.Size;
        this -> maxSize = vectorObj.maxSize;
        Array = move(vectorObj.Array);
    }
    
    // Destructor
    ~Vector() {
        delete[] Array;
    }
    
    // Assignment operator, if the content of the two arrays are different, then copy each element in array "a" to field array.
    Vector& operator=(const Vector<T>& vectorObj) {
        if (this != &vectorObj) { // Checking for equality to prevent self-assignments.
            delete[] Array; // Delete all existing elements.
            
            this -> Size = vectorObj.Size;
            this -> maxSize = vectorObj.maxSize;
            // Create a new array and copy each element in array "a" to field array by using a for loop to traverse each index.
            Array = new T[maxSize];
            for (int i = 0; i < vectorObj.Size; i++) {
                this -> Array[i] = vectorObj.Array[i];
            }
        }
        return *this; // Return the field vector.
    }
    
    // Getter functions for our two member variables
    int getSize() {
        return Size;
    }
    
    int getMaxSize() {
        return maxSize;
    }
    
    // Add a value to the array.
    void push_back(T value) {
        // As long as the number of elements is less than the maxSize(capacity) of the array, you can keep adding values to the array.
        if (Size < maxSize) {
            Array[Size] = value;
            Size++;
        }
        // When the number of elements exceeds the maxSize (no more space left), then double the maxSize in order to add more values.
        else {
            
            T* newArray = new T[maxSize * 2]; // Create a new array with the updated maxSize(Capacity).
            // Copy every value from old array to new array.
            for (int i = 0; i < maxSize; i++) {
                newArray[i] = Array[i];
            }
            delete[] Array; // Delete all info in old array
            Array = newArray; // Copy info from newArray to Array.
            Array[Size] = value; // Insert value
            Size++; // Length of vector increase by 1.
            maxSize *= 2; // Double the size.
        }
    }
    
    // Delete the last element in vector
    void pop_back() {
        // If the vector is empty, then thow string "Vector is empty".
        if (Size == 0) {
            throw string("Vector is empty.");
        }
        // When an element is removed from vector, Size decrease by 1.
        Size--;
    }
    
    // Return the last element in the vector.
    T back() {
        return Array[Size - 1];
    }
    
    // Print elements in the array (vector).
    void printInfo() {
        for (int i = 0; i < Size; i++) {
            cout << Array[i] << " ";
        }
        cout << endl;
    }
    
};

// Part a: function will randomly fill vector with integers.
void randomFillArrayInt(Vector<int>& v, int size) {
    srand(time(0));//nullptr == 0, NULL,
    for (int i = 0; i < size; i++) {
        v.push_back(rand() % 100 + 1);
    }
}
// Generate random string with random size and return the string result to where it was called.
string randomString(int strSize) {
    string ret; // result
    for (int i = 0; i < strSize; i++) {
        ret += (char)(rand() % 26 + 'a');//rand() % 26 => 0 -25;
    }
    return ret;
}

// Part b: function will randomly fill vector with strings.
void randomFillArrayString(Vector<string>& v, int size) {
    for (int i = 0; i < size; i++) {
        v.push_back(randomString(rand() % 10 + 1));
    }
}

// Part c: function will randomly fill vector with strings (move semantics used here).
void randomFillWithMoveString(Vector<string>& v, int size) {
    
    for (int i = 0; i < size; i++) {
        v.push_back(move(randomString(rand() % 10 + 1)));
    }
}
// Part d: vector from C++ library. Fill the vector with random strings with length between 1 to 10 generated from randomString function.
void fillVector(vector<string> v, int size) {
    for (int i = 0; i < size; i++) {
        v.push_back(randomString(rand() % 10 + 1));
    }
}

// Template class used for timing.
template <typename Func>
long long TimeFunc(Func f)
{
    auto begin = steady_clock::now();
    f();
    auto end = steady_clock::now();
    
    return duration_cast<milliseconds>(end - begin).count();
}

int main() {
    // Part a:  Filling vector_1 with random numbers.
    Vector<int> vector_1; // Create an empty vector call vector_1 used to store integers.
    auto vectormilliseconds = TimeFunc([&]() {randomFillArrayInt(vector_1, 1000000); });
    cout << "Time for filling vector_1 with random numbers is: " << vectormilliseconds <<  " milliseconds." << endl;
    //vector_1.printInfo();
    
    // Part b: Filling vector_2 with random strings (use ascii).
    Vector<string> vector_2; // Create an empty vector call vector_2 used to store strings.
    vectormilliseconds = TimeFunc([&]() {randomFillArrayString(vector_2, 1000000); });
    cout << "Time for filling vector_2 with random strings is: " << vectormilliseconds << " milliseconds." << endl;
    //vector_2.printInfo();
    
    // Part c: Filling vector_3 with random strings using move semantics.
    Vector<string> vector_3; // Create an empty vector call vector_3 used to store strings.
    vectormilliseconds = TimeFunc([&]() {randomFillWithMoveString(vector_3, 1000000); });
    cout << "Time for filling vector_3 with random strings using move semantics is: " << vectormilliseconds << " milliseconds." << endl;
    //vector_3.printInfo();
    
    // Part d: Using vector from C++ library
    vector<string> vector_4; // Create an empty vector call vector_4 used to store strings.
    vectormilliseconds = TimeFunc([&]() {fillVector(vector_4, 1000000); });
    cout << "Time for filling vector_4 with random strings using vector from C++ library is: " << vectormilliseconds << " milliseconds." << endl;
}




