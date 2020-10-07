//
//  main.cpp
//  Problem_7_LinkedLIst
//
//  Created by Amy Zhang on 9/24/20.
//  Copyright © 2020 Amy Zhang. All rights reserved.
//

#include <iostream>
#include<ctime>
#include<cstdlib>
#include <chrono>
using std::chrono::system_clock;
using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::milliseconds;
using namespace std;

// 7. Create your own vector and list. Time it similar to question #1
// Vector is faster for all part a, b, and c timings.

template<typename T>
class LinkList{
    
private:
    // struct -> member variables and methods are public
    struct Node{
        // Member variables for Node class
        T Info; // Info is a variable that represents the node with the value.
        Node* Next; // Next is a variable pointer that points to the next value.
        
        // Default constructor - create a default empty node
        Node(){
            Next = nullptr;
        }
        // 1 parameter constructor - create a node storing input value
        Node(T value){
            Info = value;
            Next = nullptr;
        }
        // 2 parameter constructor - create a node storing input value and pointing to another node
        Node(T value, Node* nextPtr){
            Info = value;
            Next = nextPtr;
        }
        // Setters for each field variables
        void setInfo(T Info){
            this -> Info = Info;
        }
        
        void setNext(Node* Next){
            this -> Next = Next;
        }
        
        // Getters for each field variables
        T getInfo(){
            return Info;
        }
        
        Node* getNext(){
            return Next;
        }
    };
    
// Member varibales for LinkList class
private:
    int Counter; // Variable to track the number of nodes in the list.
    Node* head; // Pointer to the first node of the list
    
    
public:
    class Iterator {
        friend class LinkedList;
    private:
        Node *nodePointer;
        
    public:
        // Default constructor - creates an iterator with a nodePointer pointing to null.
        Iterator(){
            nodePointer = nullptr;
        }
        // Regular 1 parameter constructor - takes in newPointer as the parameter and assigns it to nodePointer.
        Iterator(Node *newPointer) {
            nodePointer = newPointer;
        }
        // Overload for the comparison operator !=.
        bool operator!=(const Iterator& itr) const {
            return nodePointer != itr.nodePointer;
        }
        
        // Overload for the dereference(to get value) operator *.
        T& operator*() const {
            return nodePointer -> Info;
        }
        
        // Overload for the postincrement operator ++, i++.
        Iterator operator++(int) {
            iterator temp = *this;
            nodePointer = nodePointer -> Next;
            return temp;
        }
    };
    
    // Default constructor
    LinkList() {
        head = nullptr;
    };
    
    // Getter for Counter variable, returns counter.
    int getCounter(){
        return Counter;
    }
    
    // Counter == 0 means that the list is empty.
    bool isEmpty(){
        return Counter == 0;
    }
    
    // Add a value to the LinkList, value data type is generic.
    void add(T value){
        Node* node= new Node(value); // Create a new node with value.
        // If head is empty, set node to head
        if(head == nullptr){
            head = node;
        }
        // If head is not empty, then add to head.
        else{
            node -> Next = head;
            head = node;
        }
        // A element is added, so increase counter by 1.
        Counter++;
    }
    
    // Remove last element from LinkList
    T remove(){
        // If LinkList is empty, then return empty list.
        if(Counter == 0){
            throw string("Empty List");
        }
        
        Node* node = head;
        T ret = node -> Info;
        delete node;
        head = head -> Next;
        Counter--;
        return ret;
    }
    
    // Return iterator from beginning of list
    Iterator begin() const {
        return iterator(head);
    }
    
    // Return iterator from the end of list
    Iterator end() const {
        return Iterator(nullptr);
    }
    
    // printList function will print the initial node until it finds NULL for the Next pointer that indicate the end of the Node Chain.
    void printList(){
        Node * node = head;
        while(node != nullptr){
            cout << node -> Info << " -> ";
            node = node -> Next;
        }
        cout << "NULL" << endl;
    }
};

// Fill LinkList with random integer number between 1 to 100 and adds it to the list.
void fillList_int(LinkList<int>& list, int size){
    srand(time(0));
    for(int i = 0; i < size; i++){
        list.add(rand() % 100 + 1);
    }
}

// Generate random string with random size.
string randomString(int strSize) {
    srand(time(0));
    string ret;//result
    for (int i = 0; i < strSize; i++) {
        ret += (char)(rand() % 26 + 'a'); // rand() % 26 => 0 to 25
    }
    return ret;
}

// Fill LinkList with random strings with length between 1 to 10 and adds it to the list.
void fillList_string(LinkList<string>& list, int size){
    srand(time(0));
    for(int i = 0; i < size; i++){
        list.add(randomString(rand() % 10 + 1));
    }
}

// Function takes in a reference to string LinkList and a variable called size, then fills it with random strings with length between 1 to 10 (use move semantics).
void fillList_string_move(LinkList<string>& list, int size){
    for(int i = 0; i < size; i++){
        list.add(move(randomString(rand() % 10 + 1)));
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
    
    // Part a: Filling list_1 with random numbers.
    LinkList<int> list_1; // Create an empty list call list_1 used to store integers.
    auto vectormilliseconds = TimeFunc([&]() {fillList_int(list_1, 1000000); });
    cout << "Time for filling list_1 with random numbers is: " << vectormilliseconds << " milliseconds." << endl;
    
    // Part b: Filling list_2 with random strings (use ascii).
    LinkList<string> list_2; // Create an empty list call list_2 used to store strings.
    vectormilliseconds = TimeFunc([&]() {fillList_string(list_2, 1000000); });
    cout << "Time for filling list_2 with random strings is: " << vectormilliseconds << " milliseconds." << endl;
    
    // Part c: Filling list_3 with random strings using move semantics.
    LinkList<string> list_3; // Create an empty list call list_3 used to store strings.
    vectormilliseconds = TimeFunc([&]() {fillList_string_move(list_3, 1000000); });
    cout << "Time for filling list_3 with random strings using move semantics is: " << vectormilliseconds << " milliseconds." << endl;
    
}
