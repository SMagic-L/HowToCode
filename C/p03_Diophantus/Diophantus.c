#include<stdio.h>
#define MAX_AGE 100

double f(int);

int main()
{
	//init
	int head = 0,tail = MAX_AGE;
	int i = (head + tail) / 2;
	
	//binary search
	while(0 != f(i))
	{
		if(1 == tail - head && 0 == f(i+1))
		{
			i++;
			break;
		}
		if(f(i) > 0)
			head = i;
		else
			tail = i;
		i = (head + tail) / 2;
	}
	
	printf("����ͼ����ȥ��ʱ������ͼ%d�ꡣ",i-4);
	
	
	
	
	
}

double f(int i)
{
	return (int)i/6.0 + i/12.0 + i/7.0 + 5 + i/2.0 + 4 - i;
}
