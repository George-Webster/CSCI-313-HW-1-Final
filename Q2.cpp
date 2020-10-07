// Daniel Yoh CSCI 313-22 Group 7 
//#2: Test whether a recursive, iterative or linked-type binary search is faster by testing it on arrays of size
// 1 million, 10 million, and 100 million with arrays that are filled with random numbers going from smallest to largest.

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
bool recursive_Srch(int arr[], int low, int high, int target);
bool iterative_Srch(int arr[], int low, int high, int target);
bool linked_Srch(Node* head, int target);
void loops(const int size);

int main() {
    srand(time(NULL));               //Uses random seed to get random numbers for rand
    const int size = 1000000;
    cout << "Size 1 million:" << endl;
    loops(size);
    cout << endl;

    const int size2 = 10000000;
    cout << "Size 10 million:" << endl;
    loops(size2);
    cout << endl;

    const int size3 = 100000000;
    cout << "Size 100 million:" << endl;
    loops(size3);
    cout << endl;

    return 0;
}


void loops(const int size) {
    int* array = new int[size];    //Declares array.  Use int* to allocate on heap
    array[0] = rand();

    for (int i = 1; i < size; i++) array[i] = rand() + array[i - 1]; // For Loop fills array and linked list with random variables
    int target = rand(); //Target number to find for the binary search
    
    auto begin = high_resolution_clock::now();
    bool srch = recursive_Srch(array, 0, size - 1, target);
    auto end = high_resolution_clock::now();

    if (!srch) cout << target << " is not present in the array" << endl;
    else cout << target << " is present in the array" << endl;
    cout << "A recursive binary search is " << duration_cast<nanoseconds>(end - begin).count() << " nanoseconds long." << endl << endl;


    begin = high_resolution_clock::now();
    srch = iterative_Srch(array, 0, size - 1, target);
    end = high_resolution_clock::now();

    if (!srch) cout << target << " is not present in the array";
    else cout << target << " is present in the array";
    cout << endl << "An iterative binary search is " << duration_cast<nanoseconds>(end - begin).count() << " nanoseconds long." << endl << endl;

    //Linked Binary Search section
    struct Node* head = new Node();  //Declares linked list
    head->data = rand();
    for (int i = 0; i < size/10000; i++) insert_Node(&head, rand());

    begin = high_resolution_clock::now();
    for (int i = 0; i < 10000; i++) bool srch = linked_Srch(head, target);
    end = high_resolution_clock::now();

    if (!srch) cout << target << " is not present in the linked list";
    else cout << target << " is present in the linked list";
    cout << endl << "A linked binary search is " << duration_cast<nanoseconds>(end - begin).count() << " nanoseconds long." << endl << endl;

}


void insert_Node(struct Node** head, int data) {
    struct Node* inserted_Node = new Node();    //Create new node to insert into Linked List 
    if (*head == NULL) *head = inserted_Node; // For if the linked list is empty, makes the new node the head node
    else {
        struct Node* temp = *head;  //Initialize new node 'temp' with head node
        inserted_Node->next = NULL;   //Inserted node points to nothing because there's no node after it
        inserted_Node->data = data;   //Passes data into the inserted node
        while (temp->next) temp = temp->next;  // temp traverses from node to node until it reaches the last one in the list, when temp->next == NULL.
        temp->next = inserted_Node;  // Makes the last node point to the inserted node
    }
}


bool recursive_Srch(int arr[], int low, int high, int target) {
    if (low <= high) {
        int mid = (high + low) / 2;  // Finds the middle of the list
        if (arr[mid] == target) return true; // If target is found
        if (arr[mid] < target) return recursive_Srch(arr, mid + 1, high, target);
        return recursive_Srch(arr, low, mid - 1, target);
    };
    return false; //If target isn't in list
};

bool iterative_Srch(int arr[], int low, int high, int target) {
    while (low <= high) {
        int mid = (high + low) / 2;
        if (arr[mid] == target) return true; // If target is found
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    };
    return false; //If target isn't in list
};

bool linked_Srch(struct Node* head, int target) {
    struct Node* start = head;
    struct Node* last = NULL;

    while (last == NULL || last != start) {
        struct Node* mid = NULL;

        struct Node* toMid = start;  // This is to find the middle node of the list
        struct Node* toTail = last;
        while (toTail != last) {   // "toTail" moves two nodes at a time, while "toMid" moves one node at a time,
            toTail = toTail->next; // so by the time toTail has finished traversing to the end of the list, 
            if (toTail != last) {  // "toMid" will have reached the middle node of the Linked List
                toTail = toTail->next;
                toMid = toMid->next;
            }
        }
        mid = toMid;  // Sets "mid" to the middle node of the list

        if (mid == NULL) return 0;
        if (mid->data == target) return true; //End of function; target is found

        else if (mid->data < target) start = mid->next; //If data in the middle node is less than target
        else last = mid; //If data in the middle node is more than target
    };

    return false; //If target isn't in list
};