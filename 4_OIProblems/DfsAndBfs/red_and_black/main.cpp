#include <iostream>
#include <cstring>
using namespace std;

//const
const int MAX_SIZE = 20;
const char START_POINT = '@';
const char BLACK_POINT = '.';
const char WHITE_POINT = '#';

//struct
typedef struct{
    int x;
    int y;
} Point;
typedef struct {
    char map[MAX_SIZE][MAX_SIZE];
    bool book[MAX_SIZE][MAX_SIZE];
    Point start,mapSize;
    int solution;
} Problem;

//global
const Point nextStep[4] = {
        (Point){0,1},
        (Point){1,0},
        (Point){0,-1},
        (Point){-1,0}
};

//prototype
void getMaxBlack(Problem *problem, Point step);
Point pointPlus(Point left, Point right);
void readProblem(Problem *ptr);
bool isOutOfRange(Point mapSize, Point point);

int main()
{
    int m,n;
    Problem problem;
    int result = 0;

    while(cin >> m >> n)
    {
        if(0 == m && 0 == n)
            break;

        memset(&problem,0, sizeof(Problem));
        problem.mapSize.x = n;
        problem.mapSize.y = m;

        readProblem(&problem);
        getMaxBlack(&problem, problem.start);
        result = problem.solution;
        cout << result << endl;
    }
    return 0;
}

void readProblem(Problem *ptr)
{
    for(int i = 0;i < ptr->mapSize.x;i++)
        for (int j = 0; j < ptr->mapSize.y; ++j)
        {
            cin >> ptr->map[i][j];
            if(START_POINT == ptr->map[i][j])
            {
                ptr->start.x = i;
                ptr->start.y = j;
            }
        }
    ptr->solution = 1;
}

void getMaxBlack(Problem *problem, Point step)
{
    if(isOutOfRange(problem->mapSize,step))
        return;
    if(problem->book[step.x][step.y] || WHITE_POINT == problem->map[step.x][step.y])
        return;
    if(BLACK_POINT == problem->map[step.x][step.y])
        problem->solution++;
    problem->book[step.x][step.y] = true;
    Point tmp;
    for(Point i : nextStep)
    {
        tmp = pointPlus(step, i);
        if(isOutOfRange(problem->mapSize,tmp))
            continue;
        getMaxBlack(problem,tmp);
    }
}

bool isOutOfRange(Point mapSize, Point point)
{
    return point.x < 0 || point.x >= mapSize.x || point.y < 0 || point.y >= mapSize.y;
}

Point pointPlus(Point left, Point right)
{
    return (Point){left.x + right.x,left.y + right.y};
}

