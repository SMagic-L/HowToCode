#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

//const
const int MAX_SIZE = 200;

//struct
typedef struct {
    int x,y,t,step;
} Point;
typedef struct {
    char map[MAX_SIZE][MAX_SIZE];
    int m,n,t,solution;
    Point start;
    bool book[MAX_SIZE][MAX_SIZE][10];
} Problem;

//global
Point nextPoint[4] = {
        {0,1,0,1},
        {1,0,0,1},
        {0,-1,0,1},
        {-1,0,0,1}
};
Problem problem;

//prototype
Point pointPlus(Point a, Point b);
void bfs();
bool isOutOfRange(Point point);
void initProblem();

int main()
{
    initProblem();
    bfs();

    if(MAX_SIZE * MAX_SIZE == problem.solution)
        problem.solution = -1;
    cout << problem.solution;
    return 0;
}

void initProblem()
{
    memset(&problem,0,sizeof(Problem));
    cin >> problem.m >> problem.n >> problem.t;
    for(int i = 0;i < problem.m;i++)
        for(int j = 0;j < problem.n;j++)
        {
            cin >> problem.map[i][j];
            if('@' == problem.map[i][j])
                problem.start = {i,j,problem.t};
        }
    problem.book[problem.start.x][problem.start.y][problem.start.t] = true;
    problem.solution = MAX_SIZE * MAX_SIZE;
}

Point pointPlus(Point a, Point b)
{
    return {a.x + b.x,a.y + b.y,a.t + b.t,a.step + b.step};
}

void bfs()
{
    Point point;
    queue<Point> q;
    q.push(problem.start);

    while(!q.empty())
    {
        for(Point tmp: nextPoint)
        {
            point = pointPlus(q.front(),tmp);

            if(isOutOfRange(point) || problem.book[point.x][point.y][point.t])
                continue;

            if('+' == problem.map[point.x][point.y])
            {
                problem.solution = point.step;
                return;
            }

            if('#' == problem.map[point.x][point.y])
            {
                if (point.t > 0)
                    point.t--;
                else
                    continue;
            }

            q.push(point);
            problem.book[point.x][point.y][point.t] = true;
        }
        q.pop();
    }
}

bool isOutOfRange(Point point)
{
    return (point.x < 0 || point.y < 0 || point.x >= problem.m || point.y >= problem.n);
}
