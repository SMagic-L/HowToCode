#include<iostream>
using std::cout;
using std::endl;
using std::cin;

//global
const int LENGTH = 6;
char a[LENGTH + 1] = "";
int b[LENGTH] = {0};
int book[LENGTH] = {0};
int n = 0;

//prototype
void dfs(int); 

int main()
{
	//declaration and input	
	cin >> a;
	for(int i = 0; i<=LENGTH;i++)
	{
		if('\0' == a[i])
		{
			n = i;
			break;
		}
	}
	
	//catch exception
	if(0 == n)
		return 0;
	
	//short circuit
	if(1 == n)
	{
		cout << a[0];
		return 0;
	}
	if(2 == n)
	{
		cout << a[0] << a[1] << endl << a[1] << a[0] << endl;
		return 0;
	}
	
	//start dfs
	dfs(n);
	
	return 0;
}

void dfs(int step)
{
	//stop condition
	if(step <= 0)
	{
		for(int i = 0; i < n;i++)
			cout << a[b[i]];
		cout << endl;
		return;
	}
	
	//main body
	for(int i = 0;i<n;i++)
		if(0 == book[i])
		{
			b[n - step] = i;
			book[i] = 1;
			dfs(step - 1);
			book[i] = 0;
		} 
	
	return;
	
}
