#include<iostream>
#include<cstring>
using namespace std;

//const
const int MAX_N = 8;
const char BOARD_BLOCK = '#';

//struct
typedef struct Point {
	int x;
	int y;
} Point;
typedef struct Problem {
	bool x_book[MAX_N];
	bool y_book[MAX_N];
	Point board[MAX_N * MAX_N];
	int tail;
	int n,k,restPoint,solution;
}Problem;

//prototype
void solve(Problem* problem, int step);
void getProblem(Problem* problem, int n, int k);

int main()
{
	int n, k;
	Problem problem;
	while (cin >> n >> k)
	{
		if (-1 == n && -1 == k)
			break;
		memset(&problem, 0, sizeof(Problem));
		getProblem(&problem,n ,k );
		solve(&problem,0);
		cout << problem.solution << endl;
	}

	return 0;
}

void solve(Problem* problem, int step)
{
	//short circuit
	if (problem->restPoint <= 0)
	{
		problem->solution++;
		return;
	}
	if (step >= problem->tail)
		return;

	Point tmpPoint = problem->board[step];

	//do not step on
	solve(problem, step + 1);

	if (problem->x_book[tmpPoint.x] || problem->y_book[tmpPoint.y] )
		return;

	//can step on
	problem->x_book[tmpPoint.x] = true;
	problem->y_book[tmpPoint.y] = true;
	problem->restPoint--;
	solve(problem, step + 1);
	problem->x_book[tmpPoint.x] = false;
	problem->y_book[tmpPoint.y] = false;
	problem->restPoint++;

}
void getProblem(Problem* problem, int n, int k)
{
	problem->n = n;
	problem->k = k;
	problem->restPoint = k;
	char tmp;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			cin >> tmp;
			if (BOARD_BLOCK == tmp)
			{
				problem->board[problem->tail] = { i,j };
				problem->tail++;
			}
		}
}