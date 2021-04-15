#include<iostream>

using namespace std;

int f(int,int);

const int N = 50;

int main()
{
	//init
	int x;
	while(EOF != cin.peek() && '\n' != cin.peek())
	{
		cin >> x;
		int result = f(x,x);
		cout << result << endl;
		if('\n' == cin.peek())
			cin.get();
	}
	
	return 0;
}

int f(int num,int height)
{
	//stop condition
	if(num <= 1)
		return 1;
	if(height > num)
		return f(num,num);
	
	//init
	int result = 0;

	//move 
	for(int h = height;h > 0;h--)
		result += f(num-h,h);
	
	return result;
}


