#include<iostream>
using namespace std;

int main()
{
	//declaration
	char source[30] = "",target[30] = "";
	int n = 0,i,j,trans[30],btn[30] = {0},s[2] = {0},result = 0;
	
	
	//input and get n(the upper bound of source)
	cin >> source;
	cin >> target;
	for(i =0;i<30;i++)
	{
		if('\0' == source[i])
			break;
		n = i;
	}
		
	//get transfering state
	for(i = 0; i<=n;i++)
	{
			
		trans[i] = (int(target[i]) - int(source[i]));
		trans[i] *= trans[i];
	}
	
	//enum and calculate
	for(i = 0;i <= 1; i++)
	{
		//initialize
		btn[0] = i;
		btn[1] = (btn[0] + trans[0]) % 2;
		
		//calculate
		for(j = 2;j<=n;j++)
			btn[j] = (btn[j-1] + btn[j-2] + trans[j-1]) % 2;
			
		//check possibility
		if(trans[n] != (btn[n-1] + btn[n]) % 2)
		{
			s[i] = 99;
			continue;
		}
		
		//sum up
		for(j = 0;j<=n;j++)
			s[i] += btn[j];
			
	}
	
	//get result and output
	result = s[0];
	if(s[0] > s[1])
		result = s[1];
	if(99 == result)
		cout << "impossible";
	else
		cout << result;
	
	return 0; 
	
	
}

