#include <iostream>
#include <vector>
#include <chrono>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using std::chrono::system_clock;
using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::milliseconds;

template <typename Func>
long long TimeFunc(Func f);

bool deBruijn2(vector<int> v);
bool deBruijn3(vector<int> v);
void createDeBruijn2(vector<int> &v);
void createDeBruijn3(vector<int> &v);

int main()
{
    //seed random number
    srand(time(NULL));

    cout << "This program creates 100 random strings of length 8, and tests to see if they are De Bruijn sequences B(2,3), \nmutating them until they are if they are not.";
    cout << "\nAdditionally, it times the 100 runs and reports the results at the end." << endl << endl;
    
    //create timing sum
    long long sum = 0;

    //loop 100 times
    for (int i = 0; i < 100; i++) {
        vector<int> v;
        //seed vector
        for (int i = 0; i < 8; i++) {
            v.push_back(rand() % 2);
        }
        
        //time it
        auto timing = TimeFunc([&]() {createDeBruijn3(v); });
        sum = sum + timing;

        cout << "De Bruijn Sequence: ";
        for (int i = 0; i < 8; i++) {
            cout  << v[i] << ' ';
        }
        cout << endl;
    }
    //report the time
    cout << "\nTime elapsed: " << sum << " milliseconds." << endl;

    return 0;
}

//for an earlier model using B(2,2)
bool deBruijn2(vector<int> v) {
    int bitStrings[4][2] = { {0,0},{0,1},{1,0},{1,1} };
    bool contained[4];
    for (int i = 0; i < 4; i++) {
        contained[i] = false;
    }
    for (int i = 0; i < v.size(); i++) {
        if (bitStrings[0][0] == v[i]) {
            if (bitStrings[0][1] == v[(i + 1) % v.size()]) {
                contained[0] = true;
            }
            if (bitStrings[1][1] == v[(i + 1) % v.size()]) {
                contained[1] = true;
            }
        }
        if (bitStrings[2][0] == v[i]) {
            if (bitStrings[2][1] == v[(i + 1) % v.size()]) {
                contained[2] = true;
            }
            if (bitStrings[3][1] == v[(i + 1) % v.size()]) {
                contained[3] = true;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        if (!contained[i]) return false;
    }
    return true;
}


bool deBruijn3(vector<int> v) {
    //create all bit strings
    int bitStrings[8][3] = { {0,0,0},{0,0,1},{0,1,0},{0,1,1},{1,0,0},{1,0,1},{1,1,0},{1,1,1} };
    //array of flags, one for each string, initialized to false
    bool contained[8];
    for (int i = 0; i < 8; i++) {
        contained[i] = false;
    }
    //nested for loops test for each string, starting at each point in the vector. Additionally, it loops around.
    for (int i = 0; i < v.size(); i++) {
        if (bitStrings[0][0] == v[i]) {
            if (bitStrings[0][1] == v[(i + 1) % v.size()]) {
                if (bitStrings[0][2] == v[(i + 2) % v.size()]) {
                    contained[0] = true;
                }
                if (bitStrings[1][2] == v[(i + 2) % v.size()]) {
                    contained[1] = true;
                }
            }
            if (bitStrings[2][1] == v[(i + 1) % v.size()]) {
                if (bitStrings[2][2] == v[(i + 2) % v.size()]) {
                    contained[2] = true;
                }
                if (bitStrings[3][2] == v[(i + 2) % v.size()]) {
                    contained[3] = true;
                }
            }
        }
        if (bitStrings[4][0] == v[i]) {
            if (bitStrings[4][1] == v[(i + 1) % v.size()]) {
                if (bitStrings[4][2] == v[(i + 2) % v.size()]) {
                    contained[4] = true;
                }
                if (bitStrings[5][2] == v[(i + 2) % v.size()]) {
                    contained[5] = true;
                }
            }
            if (bitStrings[6][1] == v[(i + 1) % v.size()]) {
                if (bitStrings[6][2] == v[(i + 2) % v.size()]) {
                    contained[6] = true;
                }
                if (bitStrings[7][2] == v[(i + 2) % v.size()]) {
                    contained[7] = true;
                }
            }
        }
    }
    //if any flags have not been set to true, return false
    for (int i = 0; i < 8; i++) {
        if (!contained[i]) return false;
    }
    return true;
}

//from an earlier build using B(2,2)
void createDeBruijn2(vector<int> &v) {
    while (!deBruijn2(v)) {
        for (int i = 0; i < v.size(); i++) {
            if ((rand() % 20) == 0) {
                if (v[i] == 0) v[i] = 1;
                else v[i] = 0;
            }
        }
    }
    return;
}

//alters v until it is a De Bruijn
void createDeBruijn3(vector<int> &v) {
    while (!deBruijn3(v)) {
        for (int i = 0; i < v.size(); i++) {
            //create a 1/20, or 5% chance, of mutation
            if ((rand() % 20) == 0) {
                if (v[i] == 0) v[i] = 1;
                else v[i] = 0;
            }
        }
    }
    return;
}

//timing function
template <typename Func>
long long TimeFunc(Func f)
{
    auto begin = steady_clock::now();
    f();
    auto end = steady_clock::now();

    return duration_cast<milliseconds>(end - begin).count();
}

