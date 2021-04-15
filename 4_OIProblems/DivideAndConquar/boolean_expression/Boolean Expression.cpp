#include<iostream>

using namespace std;

bool exp();
bool item();
bool factor();
void clearSpace();
char calcOneLine();

int main()
{
	int i = 1;
	char c;
	while (EOF != cin.peek())
	{
		c = calcOneLine();
		cout << "Expression " << i << ": " << c << endl;
		i++;
	}

	return 0;
}

char calcOneLine()
{
	bool result = exp();
	if ('\n' == cin.peek())
		cin.get();
	if (result)
		return 'V';
	else
		return 'F';
}

bool exp()
{
	bool result = item();
	bool more = false;
	bool b;
	char c;
	clearSpace();
	if ('|' == cin.peek())
		more = true;
	while (more)
	{
		clearSpace();
		c = cin.get();
		b = item();
		result = (result || b);
		clearSpace();
		if (EOF == cin.peek() || ')' == cin.peek() || '\n' == cin.peek())
			more = false;
	}
	return result;
}

bool item()
{
	bool result = factor();
	bool more = false;
	bool b;
	char c;
	clearSpace();
	if ('&' == cin.peek())
		more = true;
	while (more)
	{
		clearSpace();
		c = cin.get();
		b = factor();
		result = (result && b);
		clearSpace();
		if ('|' == cin.peek() || EOF == cin.peek() || ')' == cin.peek() || '\n' == cin.peek())
			more = false;
	}
	return result;
}


bool factor()
{
	bool result = false;
	bool more = true;

	clearSpace();

	//if ! occurs
	if ('!' == cin.peek())
	{
		cin.get();
		result = !factor();
		return result;
	}

	//if () occurs
	if ('(' == cin.peek())
	{
		cin.get();
		result = exp();
		cin.get();
		return result;
	}

	//if only V or F
	char c = cin.get();
	if ('V' == c)
		result = true;
	return result;
}

void clearSpace()
{
	while (' ' == cin.peek())
		cin.get();
	return;
}
