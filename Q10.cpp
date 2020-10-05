#include <iostream>
#include <forward_list>
using namespace std;

//using a single linked list format
forward_list<int> evenOddSort(forward_list<int> L);

int main()
{
    //find out the size of the list
    int k;
    cout << "Please enter the desired length of the list: ";
    cin >> k;

    //create the list and fill it with numbers 1 to k
    forward_list<int> list1;
    for (int i = k; i > 0; i--) {
        list1.push_front(i);
    }

    //display list before sort
    cout << "The current list: ";
    forward_list<int>::iterator it;
    for (it = list1.begin(); it != list1.end(); ++it) {
        cout << *it << ' ';
    }
    cout << endl;

    //replace the list with the sorted list
    list1 = evenOddSort(list1);

    //display list after sort
    cout << "The sorted list: ";
    for (it = list1.begin(); it != list1.end(); ++it) {
        cout << *it << ' ';
    }
    cout << endl;

        return 0;
    }

    forward_list<int> evenOddSort(forward_list<int> L) {
        //create temporary list
        forward_list<int> temp;

        //create iterators for both lists
        forward_list<int>::iterator it = L.begin();
        forward_list<int>::iterator next;

        //iterate through current list
        for (it = L.begin(); it != L.end(); ++it) {
            int val = *it;

            //determine if val is even or odd
            if (val % 2 == 1) {
                //if temp is empty, the iterator next cannot be assigned or incremented
                if (temp.empty()) {
                    temp.push_front(val);
                    //once temp has an element, the iterator can be assigned
                    next = temp.begin();
                }
                else {
                    temp.push_front(val);
                    //increment the iterator so that we know where the last odd number is in temp
                    ++next;
                }
            }
            else {  //if even, insert after the last odd number in the list
                temp.insert_after(next, val);
            }
        }
        return temp;
    }