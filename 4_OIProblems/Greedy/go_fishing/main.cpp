#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

//const
const int MAX_N = 25;
const int MAX_T = 192;

//struct
typedef struct {
    int time[MAX_N],fish,n;
}Solution;
typedef struct{
    int n,h;
    int f[MAX_N],d[MAX_N],t[MAX_N];
    int fishMap[MAX_N][MAX_T];
    Solution solution;
} Problem;

//prototype
void readProblem(Problem *problem);
void solve(Problem *problem);
void showSolution(Solution solution);
Solution getCurrentSolution(Problem *problem, int interval, int stopAt);
bool betterSolution(Solution a, Solution b);

int main()
{
    //init
    int n = 0;
    Problem problem;

    while(cin >> n)
    {
        if(n <= 0)
            break;
        memset(&problem,0, sizeof(Problem));
        problem.n = n;
        readProblem(&problem);
        solve(&problem);
        showSolution(problem.solution);
    }

    return 0;
}

void showSolution(Solution solution)
{
    for(int i = 0; i < solution.n; i++)
    {
        cout << 5 * solution.time[i];
        if(i >= solution.n - 1)
            break;
        cout << ", ";
    }
    cout << endl << "Number of fish expected: " << solution.fish << endl << endl;
}

void solve(Problem *problem)
{
    //init
    int stopAt = 0, restInterval = 12 * problem->h,maxFish = 0,minJ = 0;
    Solution solution, maxSolution;
    memset(&solution,0, sizeof(Solution));
    memset(&maxSolution,0, sizeof(Solution));

    //init fishMap
    for(int i = 0;i < problem->n;i++)
    {
        if(0 == problem->d[i])
            minJ = MAX_T;
        else
            minJ = min(MAX_T, problem->f[i] / problem->d[i]);

        for(int j = 0; j <= minJ; j++)
        {
            problem->fishMap[i][j] = problem->f[i] - j * problem->d[i];
        }
    }

    //classify stop location
    for(stopAt = 0;stopAt < problem->n; stopAt++)
    {
        restInterval -= problem->t[stopAt];
        solution = getCurrentSolution(problem, restInterval, stopAt);

        if(betterSolution(solution,maxSolution))
        {
            maxSolution = solution;
            problem->solution = solution;
        }
    }
}

bool betterSolution(Solution a, Solution b)
{
    if(a.fish > b.fish)
        return true;
    if(a.fish < b.fish)
        return false;
    if(a.fish == b.fish)
    {
        for(int i = 0;i < a.n;i++)
        {
            if(a.time[i] == b.time[i])
                continue;
            return a.time[i] > b.time[i];
        }
        return false;
    }
}

Solution getCurrentSolution(Problem *problem, int interval, int stopAt)
{
    //init
    int j[MAX_T] = {0},counter = 1,tmpMax = 0,tmpMaxI = 0;
    Solution result;
    memset(&result,0, sizeof(result));

    while(counter <= interval)
    {
        tmpMax = 0;
        tmpMaxI = 0;
        for(int i = 0;i <= stopAt;i++)
            if(problem->fishMap[i][j[i]] > tmpMax)
            {
                tmpMax = problem->fishMap[i][j[i]];
                tmpMaxI = i;
            }

        result.time[tmpMaxI]++;
        result.fish += problem->fishMap[tmpMaxI][j[tmpMaxI]];
        j[tmpMaxI]++;
        counter++;
    }

    result.n = problem->n;
    return result;
}

void readProblem(Problem *problem)
{
    cin >> problem->h;
    for(int i = 0; i < problem->n;i++)
        cin >> problem->f[i];
    for(int i = 0; i < problem->n;i++)
        cin >> problem->d[i];
    for(int i = 1; i < problem->n;i++)
        cin >> problem->t[i];
}