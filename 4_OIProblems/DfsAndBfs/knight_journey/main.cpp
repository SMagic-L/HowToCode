#include <iostream>
#include <cstring>
using namespace std;

//const
const int MAX_LENGTH = 8;
const int MAX_SQUARE = 26;

//struct
typedef struct {
    int x;
    int y;
} Point;
typedef struct {
    bool book[MAX_LENGTH][MAX_LENGTH];
    Point route[MAX_SQUARE];
    int tail,x,y;
    bool solved;
} Problem;

//global
Point nextStep[8] = {
    {-2, -1},
    {-2, 1},
    {-1,-2},
    {-1,2},
    {1,-2},
    {1,2},
    {2,-1},
    {2,1}
};

//prototype
void dfs(Problem* problem, Point step);
bool shortCircuitSucceed(int p,int q);
void showSolution(Problem* problem);
bool isBlocked(Problem* problem, Point point);
Point pointPlus(Point left, Point right);

int main()
{
    //init
    int n;
    Problem problem;
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        memset(&problem, 0, sizeof(Problem));
        cin >> problem.y >> problem.x;
        cout << "Scenario #" << i << ":" << endl;
        if (shortCircuitSucceed(problem.x, problem.y))
            continue;
        dfs(&problem,{0,0});
        if(!problem.solved)
            cout << "impossible" << endl << endl;
    }
    return 0;
}

void dfs(Problem* problem, Point step)
{
    if (isBlocked(problem, step) || problem->solved)
        return;

    problem->book[step.x][step.y] = true;
    problem->route[problem->tail] = step;
    problem->tail++;

    if (problem->tail >= problem->x * problem->y)
    {
        showSolution(problem);
        problem->solved = true;
        return;
    }

    Point tmp = {0,0};
    for (Point i : nextStep)
    {
        tmp = pointPlus(step, i);
        dfs(problem, tmp);
    }

    problem->book[step.x][step.y] = false;
    problem->tail--;
    return;
}
bool shortCircuitSucceed(int p, int q)
{
    if (1 == p && 1 == q)
    {
        cout << "A1" << endl << endl;
        return true;
    }
    if (p <= 2 || q <= 2)
    {
        cout << "impossible" << endl <<endl;
        return true;
    }

    return false;
}

bool isBlocked(Problem* problem, Point point)
{
    if (problem->book[point.x][point.y])
        return true;
    
    return (point.x < 0 || point.x >= problem->x || point.y < 0 || point.y >= problem->y);
}

void showSolution(Problem* problem)
{
    char tmp;
    for (int i = 0; i < problem->tail; i++)
    {
        tmp = 'A' + problem->route[i].x;
        cout << tmp << (problem->route[i].y + 1);
    }
    cout << endl << endl;
}

Point pointPlus(Point left, Point right)
{
    return { left.x + right.x,left.y + right.y };
}
