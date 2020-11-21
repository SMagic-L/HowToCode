#include<stdio.h>

void hanoi(int,char,char,char);

int main()
{
	hanoi(64,'A','B','C');
	return 0;
}

void hanoi(int n, char from,char pass,char to)
{
	//stop condition
	if(1 == n)
	{
		printf("%c -> %c\n",from,to);
		return;
	}
	
	//Ҫ�ƶ�n����ֻ���ƶ�n-1����1��(�ɹ����� 
	hanoi(n-1,from,to,pass);
	printf("%c -> %c\n",from,to);
	hanoi(n-1,pass,from,to);
	return;
} 
