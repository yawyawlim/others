// Subset_Sum_DP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

vector <int> w;
vector <int> w_;				//to record reverse order of w
vector <int> solution;			//the solution sequence
vector<vector<bool>> DPtab;		//the table to record the overlapped subproblem in DYNAMIC PROGRAMMING

void SubsetSum(int numofset, int target, vector<int>w)
{
	DPtab.resize(numofset + 1);					//num of rows = numofset+1

	for (int i = 0; i < numofset + 1; i++)
		DPtab[i].resize(target + 1, false);		
	/*
	-num of columns = target value + 1
	-Initialize the whole DPtable as false
	*/

	for (int i = 0; i < numofset + 1; i++)
		DPtab[i][0] = true;						//the first column all true
	/*
		if target =0, no mather the subset is {} or {x1} or {x1,x2} or {x1,...,xn}
		I can still get the target,so it is true
	*/

	for (int i = 1; i < numofset + 1; i++)
	{
		for (int j = 1; j < target + 1; j++)
		{
			if (j < w[i])
				DPtab[i][j] = DPtab[i - 1][j];

			else {
				DPtab[i][j] = DPtab[i - 1][j] || DPtab[i - 1][j - w[i]];
			}
		}
	}
	/*
					DPtab[i-1][j]							j<w[i]		
	DPtab[i][j]={	
					DPtab[i-1][j] || DPtab[i-1][j-w[i]]		j>=w[i]
	*/

	if (DPtab[numofset][target])		//backtrack to get solution
	{
		int i = numofset;
		int j = target;
		solution.resize(numofset + 1,0);
		int k = 1;

		while (i > 0)
		{
			if (DPtab[i - 1][j])
			{
				solution[k++] = 0;
				i--;
			}
			else
			{
				solution[k++] = 1;
				j -= w[i];
				i--;
			}
		}
	}
	if (DPtab[numofset][target]) {
		for (int i = 1; i < numofset + 1; i++)
		{
			cout << solution[i] << " ";
		}
	}
	cout << endl;
}

int main()
{
	int tests = 3;
	int target = 0;
	int solution;

	int numofset;
	while (tests--)
	{
		cout << "How many numbers in this set?" << endl;
		cin >> numofset;
		w.resize(numofset + 1);
		w_.resize(numofset + 1);
		cout << "Now key in the numbers of the set :" << endl;
		for (int i = 1; i < numofset + 1; i++)
			cin >> w[i];

		int n = numofset;
		for (int i = 1; i < numofset + 1; i++)
			w_[i] = w[n--];		//reverse the w vector


		cout << "What is the target value?" << endl;
		cin >> target;

		SubsetSum(numofset, target, w_);
		cout << endl;

	}//end while(n--)
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
