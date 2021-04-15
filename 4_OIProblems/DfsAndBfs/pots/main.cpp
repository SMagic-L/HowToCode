#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;

//const
const int MAX_SIZE = 101;

//struct
enum OptType
{
    FILL,
    DROP,
    POUR
};
typedef struct
{
    int x,y,step;
    int from, to;
    OptType opt;
} Point;

//global
int a = 0,b = 0,c = 0;
bool book[MAX_SIZE][MAX_SIZE] = {};
Point preStep[MAX_SIZE][MAX_SIZE];

//prototype
Point bfs();
void showRoute(Point result);
Point getNextStep(Point now, int index);
bool isOutOfRange(Point p);
bool isResult(Point p);
void printPoint(Point p);

int main()
{
    //init
    memset(&preStep,0,sizeof(Point) * MAX_SIZE * MAX_SIZE);
    cin >> a >> b >> c;
    Point result = bfs();
    if(-1 == result.x && -1 == result.y)
        cout << "impossible";
    else
    {
        cout << result.step << endl;
        showRoute(result);
    }

    return 0;
}

Point bfs()
{
    //init
    queue<Point> q;
    q.push({0,0,0});
    preStep[0][0] = {0,0,0};
    Point tmp;
    Point result = {-1,-1,0};

    while(!q.empty())
    {
        for(int i = 1;i <= 6; i++)
        {
            tmp = getNextStep(q.front(),i);
            if(isOutOfRange(tmp) || book[tmp.x][tmp.y])
                continue;

            q.push(tmp);
            preStep[tmp.x][tmp.y] = q.front();
            book[tmp.x][tmp.y] = true;

            if(isResult(tmp))
            {
                result = tmp;
                return result;
            }
        }
        q.pop();
    }

    return result;
}

void showRoute(Point result)
{
    stack<Point> routeInverser;
    Point tmp = result;
    while(tmp.x != 0 || tmp.y != 0)
    {
        routeInverser.push(tmp);
        tmp = preStep[tmp.x][tmp.y];
    }
    while(!routeInverser.empty())
    {
        printPoint(routeInverser.top());
        routeInverser.pop();
    }

}

Point getNextStep(Point now, int index)
{
    Point result = now;
    switch(index)
    {
        case 1:
            result.x = a;
            result.to = 1;
            result.opt = FILL;
            break;
        case 2:
            result.y = b;
            result.to = 2;
            result.opt = FILL;
            break;
        case 3:
            result.x = 0;
            result.from = 1;
            result.opt = DROP;
            break;
        case 4:
            result.y = 0;
            result.from = 2;
            result.opt = DROP;
            break;
        case 5:
            result.x = min(a,now.x + now.y);
            result.y = now.x + now.y - result.x;
            result.from = 2;
            result.to = 1;
            result.opt = POUR;
            break;
        case 6:
            result.y = min(b,now.x + now.y);
            result.x = now.x + now.y - result.y;
            result.from = 1;
            result.to = 2;
            result.opt = POUR;
            break;
        default:
            cout << "switch error" << endl;
    }
    result.step++;
    return result;
}

void printPoint(Point p)
{
    switch (p.opt)
    {
        case FILL:
            cout << "FILL(" << p.to << ")" << endl;
            break;
        case DROP:
            cout << "DROP(" << p.from << ")" << endl;
            break;
        case POUR:
            cout << "POUR(" << p.from << "," << p.to << ")" << endl;
            break;
        default:
            break;
    }
}

bool isOutOfRange(Point p)
{
    return (p.x < 0 || p.x > a || p.y < 0 || p.y > b);
}

bool isResult(Point p)
{
    return (c == p.x || c == p.y);
}