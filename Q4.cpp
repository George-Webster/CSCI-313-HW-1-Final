// Daniel Yoh CSCI 313-22 Group 7 
//#4: Compare the times it takes to sort a random array vs a linked list with a bubble sort.

#include <iostream>
#include <stdio.h>     // These three are for
#include <stdlib.h>   // generating random 
#include <time.h>    // variables with rand
#include <chrono>                 // These two are for 
using namespace std::chrono;     // measuring execution time 
using namespace std;

struct Node {  // Linked List
public:
    Node* next{ nullptr };
    int data = 0;
};

void insert_Node(struct Node** head_Node_Reference, int data); //Function declaration for adding new node to Linked List
int array_Sort(int arr[], int x); //Function declaration for array bubble sort
int lList_Sort(struct Node** head, int x); //Function declaration for Linked List bubble sort

int main() {
    srand(time(nullptr));             //Uses random seed to get random numbers for rand
    const int size = 35000;         //Size of the array and linked list
    int array[size];               //Declares array
    struct Node* head = new Node();  //Declares linked list
    array[0] = rand();
    head->data = array[0];
    for (int i = 1; i < size; i++) {
        array[i] = rand();     // For Loop fills array and linked list 
        insert_Node(&head, array[i]); // with random variables 
    }

    int array_Time = array_Sort(array, size); //Calls function to time the bubble sort for an array
    int lList_Time = lList_Sort(&head, size); //Calls function to time the bubble sort for a Linked List
    cout << "The execution time for an array bubble sort is: " << array_Time << " microseconds." << endl;
    cout << "The execution time for a linked list bubble sort is: " << lList_Time << " microseconds." << endl;
    if (array_Time < lList_Time) cout << "It takes less time to bubble sort an array than a linked list.";
    else cout << "It takes less time to bubble sort a linked list than an array.";
    return 0;
}

void insert_Node(struct Node** head, int data) {
    struct Node* inserted_Node = new Node();    //Create new node to insert into Linked List 
        struct Node* temp = *head;  //Initialize new node 'temp' with head node
        inserted_Node->next = NULL;   //Inserted node points to nothing because there's no node after it
        inserted_Node->data = data;   //Passes data into the inserted node
        while (temp->next) temp = temp->next;  // temp traverses from node to node until it reaches the last one in the list, when temp->next == NULL.
        temp->next = inserted_Node;  // Makes the last node point to the inserted node
    
}

int array_Sort(int array[], int size) { //Array bubble sort function
    auto begin = high_resolution_clock::now();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {  //Swaps the elements if the previous one is larger than the next one
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - begin).count();
}

int lList_Sort(struct Node** head, int size) {
    struct Node** new_Head = head;
    auto begin = high_resolution_clock::now();
    for (int i = 0; i < size; i++) {
        new_Head = head;
        for (int j = 0; j < size - i - 1; j++) {
            struct Node* ptr = *new_Head;
            struct Node* next_Ptr = ptr->next;

            if (ptr->data > next_Ptr->data) {  //Swaps the elements if the previous one is larger than the next one
                int temp = ptr->data;
                ptr->data = next_Ptr->data;
                next_Ptr->data = temp;
            }
            new_Head = &(*new_Head)->next;
        }
    }
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - begin).count();
}
