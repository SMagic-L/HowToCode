#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

//const
const int MAX_N = 1000;

//struct
typedef struct {
    int x,y;
} IntPoint;
typedef struct {
    double x,y;
} DoublePoint;
typedef struct {
    int n,d;
    IntPoint island[MAX_N];
    DoublePoint radarRange[MAX_N];
} Problem;

//prototype
int solve(Problem *problem);
bool initProblem(Problem *problem, int n, int d);
bool isCovered(Problem *problem, int head, int tail);

int cmpRadarRange(const void *a, const void *b);

int main()
{
    //init
    Problem problem;
    int n,d,num = 1, result = 0;

    while(cin >> n >> d)
    {
        if(0 == n && 0 == d)
            break;
        if(!initProblem(&problem,n,d))
            result = -1;
        else
            result = solve(&problem);
        cout << "Case " << num << ": " << result << endl;
        num++;
    }

    return 0;
}

bool initProblem(Problem *problem, int n, int d)
{
    //init
    double delta;
    memset(problem,0, sizeof(Problem));
    problem->n = n;
    problem->d = d;

    //read data
    for(int i = 0;i < n;i++)
    {
        cin >> problem->island[i].x >> problem->island[i].y;
        delta = d * d - problem->island[i].y * problem->island[i].y;

        //impossible to reach island
        if(delta < 0)
            return false;

        delta = sqrt(delta);
        problem->radarRange[i].x = problem->island[i].x - delta;
        problem->radarRange[i].y = problem->island[i].x + delta;
    }

    //sort radar range
    qsort(problem->radarRange, n, sizeof(DoublePoint), cmpRadarRange);

    return true;
}

int cmpRadarRange(const void *a, const void *b)
{
    auto * c = (DoublePoint*)a;
    auto * d = (DoublePoint*)b;
    double opt = c->x  - d->x;
    if(opt < 0)
        return -1;
    else if (0 == opt)
        return 0;
    else
        return 1;
}

int solve(Problem *problem)
{
    //short circuit
    if(problem->d <= 0)
        return -1;

    //init
    int result = 1,head = 0;

    for(int i = 0;i < problem->n;i++)
    {
        if(isCovered(problem, head, i))
            continue;
        head = i;
        result++;
    }

    return result;
}

bool isCovered(Problem *problem, int head, int tail)
{
    if(head == tail)
        return true;
    float radar = problem->radarRange[tail].x;
    for(int i = head;i < tail;i++)
    {
        if(problem->radarRange[i].y < radar)
            return false;
    }
    return true;
}

