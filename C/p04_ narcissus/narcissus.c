#include<stdio.h>

int main()
{
	//init
	int a = 0,b = 0,c = 0;
	
	for(a = 1;a<=9;a++)
		for(b = 0;b<=9;b++)
			for(c = 0;c<=9;c++)
				if(100*a + 10*b + c == a*a*a + b*b*b + c*c*c)
					printf("%d\n",100*a + 10*b + c);
					
	return 0;
}
