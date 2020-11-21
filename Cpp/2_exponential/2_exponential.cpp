#include<iostream>
#include<string>
using namespace std;

const int BK_LENGTH = 16;

string exp(int);

int main()
{
	int a;
	cin >> a;
	string r = exp(a);
	while(r.find("2(1)") != string::npos)
		r = r.replace(r.find("2(1)"),4,"2");
	cout << r;
	return 0;
}

string exp(int num)
{
	//stop condition
	if(0 == num)
		return "0";
	if(1 == num)
		return "1";
	if(2 == num)
		return "2";
			
	//declaration
	int book[BK_LENGTH] = {0};
	int m = num, head = -1, tail = 0;
	
	//get exp num in book
	while(m != 0)
	{
		book[tail] = m % 2;
		m /= 2;
		if(1 == book[tail] && -1 == head)
			head = tail;
		tail++;	
	}
	
	//do recursive
	string result = "2(" + exp(tail-1) + ")";
	for(int i = tail - 2;i >= head;i--)
	{
		if(0 == book[i])
			continue;
		result = result + "+2(" + exp(i) + ")";
	}
	
	return result;
	
}


