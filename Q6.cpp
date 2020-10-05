#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int convertChar(char a);
char convertInt(int a);
vector<int> encode(vector<int> text, vector <int> key);
vector<int> decode(vector<int> text, vector <int> key);
double keyScore(vector<int> text, vector<int> key);
double elementScore(vector<int> text, vector<int> key, int keyPosition);

int main()
{
    const int LENGTH = 32;
    //read the text from a named file into a string
    string str, line;
    ifstream f("SandwormIntro.txt");
    if (f.is_open()) {
        while (getline(f, line))
        {
            str = str + line;
        }
        f.close();
    }
    else cout << "Unable to open file";

    //convert the string to a vector of integers (0-25) for each letter
    vector <int> v;
    for (int i = 0; i < str.size(); i++) {
        if (convertChar(str[i]) != -1) {
            v.push_back(convertChar(str[i]));
        }
    }

    //generate secret key
    vector <int> secretKey;
    srand(time(NULL));
    for (int i = 0; i < LENGTH; i++) {
        secretKey.push_back(rand() % 26);
    }

    //encode v with the secret key
    v = encode(v, secretKey);

    //create a list of keys that pass a certain threshold in terms of key score
    vector<vector<int>> keyList;
    while (keyList.size() != 30) {
        vector<int> temp;
        for (int i = 0; i < LENGTH; i++) {
            temp.push_back(rand() % 26);
        }
        if (keyScore(v, temp) > 4.2) keyList.push_back(temp);
    }

    //output the keys for example
    for (auto it = keyList.begin(); it != keyList.end(); ++it) {
        for (auto keyIt = (*it).begin(); keyIt != (*it).end(); ++keyIt) {
            cout << *keyIt << ' ';
        }
        cout << "\tScore: " << keyScore(v, *it);
        cout << endl;
    }
    cout << endl;

    //create a "FrankenKey" that takes the best performing element for each position from the list of keys
    vector<int> frankenKey;
    for (int i = 0; i < LENGTH; i++) {
        double max = 0.0;
        int element = 0;
        for (int j = 0; j < keyList.size(); j++) {
            double val = elementScore(v, keyList[j], i);
            if (max < val) {
                max = val;
                element = keyList[j][i];
            }
        }
        frankenKey.push_back(element);
    }

    cout << "Franken Key: ";
    for (auto x = frankenKey.begin(); x != frankenKey.end(); ++x) {
        cout << *x << ' ';
    }

    cout << "Score: " << keyScore(v, frankenKey) << endl << endl;

    cout << "Secret Key: ";
    for (auto x = secretKey.begin(); x != secretKey.end(); ++x) {
        cout << *x << ' ';
    }

    cout << "Score: " << keyScore(v, secretKey) << endl;

    return 0;
}

//simple functions for converting characters to integers. Note that if the character is not a letter, it returns -1
int convertChar(char a) {
    if (a == 'A' || a == 'a') return 0;
    if (a == 'B' || a == 'b') return 1;
    if (a == 'C' || a == 'c') return 2;
    if (a == 'D' || a == 'd') return 3;
    if (a == 'E' || a == 'e') return 4;
    if (a == 'F' || a == 'f') return 5;
    if (a == 'G' || a == 'g') return 6;
    if (a == 'H' || a == 'h') return 7;
    if (a == 'I' || a == 'i') return 8;
    if (a == 'J' || a == 'j') return 9;
    if (a == 'K' || a == 'k') return 10;
    if (a == 'L' || a == 'l') return 11;
    if (a == 'M' || a == 'm') return 12;
    if (a == 'N' || a == 'n') return 13;
    if (a == 'O' || a == 'o') return 14;
    if (a == 'P' || a == 'p') return 15;
    if (a == 'Q' || a == 'q') return 16;
    if (a == 'R' || a == 'r') return 17;
    if (a == 'S' || a == 's') return 18;
    if (a == 'T' || a == 't') return 19;
    if (a == 'U' || a == 'u') return 20;
    if (a == 'V' || a == 'v') return 21;
    if (a == 'W' || a == 'w') return 22;
    if (a == 'X' || a == 'x') return 23;
    if (a == 'Y' || a == 'y') return 24;
    if (a == 'Z' || a == 'z') return 25;
    return -1;
}

//Simple function to convert integers to characters. Note that if a<0 or a>25, it returns & to indicate an error
char convertInt(int a) {
    if (a == 0) return 'A';
    if (a == 1) return 'B';
    if (a == 2) return 'C';
    if (a == 3) return 'D';
    if (a == 4) return 'E';
    if (a == 5) return 'F';
    if (a == 6) return 'G';
    if (a == 7) return 'H';
    if (a == 8) return 'I';
    if (a == 9) return 'J';
    if (a == 10) return 'K';
    if (a == 11) return 'L';
    if (a == 12) return 'M';
    if (a == 13) return 'N';
    if (a == 14) return 'O';
    if (a == 15) return 'P';
    if (a == 16) return 'Q';
    if (a == 17) return 'R';
    if (a == 18) return 'S';
    if (a == 19) return 'T';
    if (a == 20) return 'U';
    if (a == 21) return 'V';
    if (a == 22) return 'W';
    if (a == 23) return 'X';
    if (a == 24) return 'Y';
    if (a == 25) return 'Z';
    return '&';
}

//takes in a text vector of integers and a key vector of integers, and shifts each text letter by the key letter, modulo 26
vector<int> encode(vector<int> text, vector<int> key) {
    vector <int> temp;
    auto keyIt = key.begin();
    for (auto textIt = text.begin(); textIt != text.end(); ++textIt) {
        temp.push_back((*textIt + *keyIt) % 26);
        ++keyIt;
        if (keyIt == key.end()) keyIt = key.begin();
    }
    return temp;
}

//takes in a text vector of ciphertext integers and a key vector of integers, and subtracts the key letter from the text letter, adding 26 if negative
vector<int> decode(vector<int> text, vector <int> key) {
    vector <int> temp;
    auto keyIt = key.begin();
    for (auto textIt = text.begin(); textIt != text.end(); ++textIt) {
        if ((*textIt - *keyIt) >= 0) {
            temp.push_back(*textIt - *keyIt);
        }
        else {
            temp.push_back(26 + *textIt - *keyIt);
        }
        ++keyIt;
        if (keyIt == key.end()) keyIt = key.begin();
    }
    return temp;
}

//uses the frequencies of letters in the english language to test whether a key decodes ciphertext into English-like text, returns a score
double keyScore(vector<int> text, vector<int> key) {
    vector<int> temp = decode(text, key);
    double count = 0.0;
    double frequency[26] = { 8.2, 1.5, 2.8, 4.3, 13, 2.2, 2, 6.1, 7, 0.15, 0.77, 4, 2.4, 6.7, 7.5, 1.9, 0.095, 6, 6.3, 9.1, 2.8, 0.98, 2.4, 0.15, 2, 0.074 };
    double alphabet[26];
    for (int i = 0; i < 26; i++) {
        alphabet[i] = 0.0;
    }
    for (auto tempIt = temp.begin(); tempIt != temp.end(); ++tempIt) {
        for (int i = 0; i < 26; i++) {
            if ((*tempIt) == i) alphabet[i] = alphabet[i] + 1.0;
        }
        count = count + 1.0;
    }
    double sum = 0.0;
    for (int i = 0; i < 26; i++) {
        sum = sum + ((alphabet[i] * frequency[i]) / count);
    }
    return sum;
}

//uses the same frequencies as keyScore, but to return a score for a single element of the key, note that the loop jumps by key.size()
double elementScore(vector<int> text, vector<int> key, int keyPosition) {
    vector<int> temp = decode(text, key);
    double count = 0.0;
    double frequency[26] = { 8.2, 1.5, 2.8, 4.3, 13, 2.2, 2, 6.1, 7, 0.15, 0.77, 4, 2.4, 6.7, 7.5, 1.9, 0.095, 6, 6.3, 9.1, 2.8, 0.98, 2.4, 0.15, 2, 0.074 };
    double alphabet[26];
    for (int i = 0; i < 26; i++) {
        alphabet[i] = 0.0;
    }
    for (int x = keyPosition; x < temp.size(); x = x + key.size()) {
        for (int i = 0; i < 26; i++) {
            if (temp[x] == i) alphabet[i] = alphabet[i] + 1.0;
        }
        count = count + 1.0;
    }
    double sum = 0.0;
    for (int i = 0; i < 26; i++) {
        sum = sum + ((alphabet[i] * frequency[i]) / count);
    }
    return sum;
}