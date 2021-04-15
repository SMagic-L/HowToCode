#include<iostream>
using namespace std;

//public variable
int c[9] = {0};
int pattern[9] = {0};

//adjoint matrix
const int P[9][9] = 
{
	{-1, 3,-1, 3,-1,-2,-1,-2, 4},
	{ 2,-1, 2,-1, 2,-1,-3, 4,-3},  
	{-1, 3,-1,-2,-1, 3, 4,-2,-1},  
	{ 2,-1,-3,-1, 2, 4, 2,-1,-3},
	{ 2,-1, 2,-1,-3,-1, 2,-1, 2},  
	{-3,-1, 2, 4, 2,-1,-3,-1, 2},   
	{-1,-2, 4, 3,-1,-2,-1, 3,-1},
	{-3, 4,-3,-1, 2,-1, 2,-1, 2},
	{ 4,-2,-1,-2,-1, 3,-1, 3,-1}
};

int main()
{
	//declaration and input
	int i = 0,j = 0;
	for(i = 0;i<9;i++)
		cin >> c[i];
	
	//calculate
	for(i = 0;i < 9;i++)
		for(j = 0;j < 9; j++)
			pattern[j] += c[i] * P[i][j]; 
	
	//output
	for(i = 1;i<10;i++)
	{
		if(pattern[i-1] < 0)
			pattern[i-1] += 4;
		pattern[i-1] %= 4;
		for(j = 0;j < ((4-pattern[i-1]) % 4);j++)
			cout << i << " ";
	}

	return 0;	
}


