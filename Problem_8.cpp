//
//  main.cpp
//  Problem_8
//
//  Created by Amy Zhang on 9/20/20.
//  Copyright © 2020 Amy Zhang. All rights reserved.
//

#include <iostream>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

// 8. Create a ​templated class​ that ​effectively f​inds all possibilities of a list of random numbers that adds to some s.


template <class T>
class Question8{
    
private:
    // Recursively find all possible solutions that add up to target.
    // sum is the current sum of all elements in solution vector.
    // results stores all possible solutions.
    // nums is the original number vector. ex: [1, 2, 3, 4, 5, 6, 8, 9, 10]
    // target is the "sum" in main function.
    void findAllSolutionHelper(const vector<T>& nums, vector<vector<T>>& results, vector<T>& solution, int index, T sum, T target){
        for(int i = index; i < nums.size(); i++){
            solution.push_back(nums[i]);
            sum += nums[i];
            // sum == target means that a solution is found
            if(sum == target){
                // ret is the name of pointer. the pointer points to vector. Right hand side is calling copy constructor.
                vector<T>* ret = new vector<T>(solution);
                // ret is a pointer.
                // Need to dereference to become a vector type.
                // Add the solution found to result vector.
                results.push_back(*ret);
            }
            // Recursive call to find ALL possible solutions that add up to target sum.
            findAllSolutionHelper(nums, results, solution, i+1, sum, target);
            solution.pop_back(); // Remove last element.
            sum -= nums[i]; // Subtract the element that was removed from the sum.
        }
    }
    
public:
    vector<vector<T>>  findAllSolution(const vector<T>& numbers, T s){
        // all possible results.
        vector<vector<T>> results;// results is a pointer to vector whose element is also a vector of type T. Call default constructor.
        vector<T> solution;// Stores one possible solution, e.x: if target sum is 10, then a possible vector stored inside solution could be [1,2,3,4].
        // Call findAllSolutionHelper function.
        findAllSolutionHelper(numbers, results,solution, 0 ,0, s);
        return results;
    }
    // Prints the original vector nums.
    void printVector(const vector<T>& v){
        cout << "*******Vector******" << endl;
        for(int i = 0; i < v.size(); i++){
            cout << v[i] << " ";
        }
        cout << endl;
        cout << "*******end*********" << endl;
    }
};
int main(){
    
    // Intialize a integer vector nums.
    vector<int> nums;
    // Vector nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
    for(int i = 0; i < 10; i++){
        nums.push_back(i + 1);
    }
    // Declare a integer vector using the template class.
    Question8<int> q;
    // Call the printVector function and print the random generated numbers in the vector.
    q.printVector(nums);
    // Find all the different combinations of numbers that adds up to this sum variable.
    int sum;
    // Ask user to enter a number for sum and read in the number.
    cout << "Enter a number for sum: ";
    cin >> sum;
    // Declare a integer vector p_solutions that stores ALL possbile solutions stored in sub-vectors that adds up to sum. Call findAllSolution function in template class.
    vector<vector<int>> p_solutions = q.findAllSolution(nums, sum);
    // Check if p_solutions is empty, which stores all the possible solutions for the target sum returned back from the findAllSolution function. If it is empty; will let user know that there's NO numbers in the orignal vector that adds up to the target sum.
    if(p_solutions.empty()){
        cout << "No possible solutions with " << sum << " as sum." << endl;
        return 0;
    }
    auto solutions = p_solutions;
    // Print the vectors that stores the possible solutions that add up to the target (sum) that was entered by the user.
    for(int i = 0; i < solutions.size(); i++){
        vector<int> solution = solutions[i];
        for(int i = 0; i < solution.size(); i++){
            cout << solution[i] <<" ";
        }
        cout << endl;
    }
}


