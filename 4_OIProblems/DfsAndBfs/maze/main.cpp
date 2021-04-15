#include <iostream>
#include <cstring>
#include <queue>
#include <stack>
using namespace std;

//const
const int SIZE = 5;

//global
typedef struct
{
    int x,y;
} Point;
Point nextStep[4] = {
    {0,1},
    {1,0},
    {0,-1},
    {-1,0}
};
int map[SIZE][SIZE] = {0};
bool book[SIZE][SIZE] = {};
Point preStep[SIZE][SIZE];

//prototype
void bfs();
Point pointPlus(Point a, Point b);
bool isOutOfRange(Point p);
bool isBlocked(Point p);
void output();

int main()
{
    //init
    memset(&preStep,0,sizeof(Point) * SIZE * SIZE);
    for(int i = 0; i < SIZE;i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            cin >> map[i][j];
        }
    }

    //bfs search
    bfs();

    //output
    output();

    return 0;
}

void bfs()
{
    queue<Point> q;
    Point tmp = {0,0};
    q.push(tmp);
    book[0][0] = true;

    while(q.front().x != SIZE-1 || q.front().y != SIZE-1)
    {
        for(Point i : nextStep)
        {
            tmp = pointPlus(i,q.front());
            if(isOutOfRange(tmp) || isBlocked(tmp) || book[tmp.x][tmp.y])
                continue;
            preStep[tmp.x][tmp.y] = q.front();
            book[tmp.x][tmp.y] = true;
            q.push(tmp);
        }
        q.pop();
    }

}

void output()
{
    stack<Point> route;
    Point tmp = {SIZE-1,SIZE-1};
    route.push(tmp);
    while(tmp.x != 0 || tmp.y != 0)
    {
        tmp = preStep[tmp.x][tmp.y];
        route.push(tmp);
    }
    while(!route.empty())
    {
        cout << "(" << route.top().x << ", " << route.top().y << ")" <<endl;
        route.pop();
    }
}

Point pointPlus(Point a, Point b)
{
    return {a.x + b.x, a.y + b.y};
}

bool isOutOfRange(Point p)
{
    return (p.x < 0 || p.x >= SIZE || p.y < 0 || p.y >= SIZE);
}

bool isBlocked(Point p)
{
    return map[p.x][p.y];
}
