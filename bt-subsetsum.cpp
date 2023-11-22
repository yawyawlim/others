// subset problem analyse.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool flag = true;       //global variable

int subset_backtrack(vector<int> temp, vector<int> weight, vector<int> visited, int x, int target_weight,
    int N, int sum, int remaining) {
    visited[x] = 1;     //marked
    if ((sum + weight[x] == target_weight && flag==true)) {
        cout << "Solution:" << endl;
        for (int i = 0; i < N; i++) {       //cout data according to the original position of data
            for (int j = N-1; j >= 0; j--) {
                if (temp[i] == weight[j]) {
                    cout << visited[j] << " ";
                    weight[j] = -1;
                }
            }
        }
        cout << endl;
        flag = false;
        return 0;
    }

    //search left side tree
    if (sum + weight[x] + weight[x + 1] <= target_weight) {   
        subset_backtrack(temp, weight, visited, x + 1, target_weight, N, sum + weight[x], remaining - weight[x]);
    }

    //search right side tree
    if ((sum + remaining - weight[x] >= target_weight) && (sum + weight[x + 1] <= target_weight)) {
        visited[x] = 0;     //reset and restore
        subset_backtrack(temp, weight, visited, x + 1, target_weight, N, sum, remaining - weight[x]);
    }
}

int main()
{
    int case_num = 3;
    while (case_num) {
        cout << "case " << 4 - case_num << ":" << endl;
        flag = true;
        case_num--;
        int N, target_weight, sum = 0, remaining = 0;

        cout << "number of subset" << endl;
        cin >> N;

        vector<int> weight;
        vector<int> visited;
        vector<int> temp;
        weight.resize(N);
        visited.resize(N);
        temp.resize(N);

        cout << "target weight" << endl;
        cin >> target_weight;

        cout << "data of subset" << endl;
        for (int i = 0; i < N; i++) {    //initialize
            cin >> weight[i];
            temp[i] = weight[i];    //temp array use to memorize the original positon of data
            visited[i] = 0;
            remaining = remaining + weight[i];
        }
        sort(weight.begin(), weight.end());     //data sort
        subset_backtrack(temp, weight, visited, 0, target_weight, N, sum, remaining);
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
