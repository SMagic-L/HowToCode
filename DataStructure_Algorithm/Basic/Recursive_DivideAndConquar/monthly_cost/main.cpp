#include <iostream>
#include <fstream>

using namespace std;

//prototype
int SearchMinCost(int left,int right);
bool IsCostFeasible(int cost);
bool Init();

//global
const int MAX_N = 100000;
const int MAX_DAY_COST = 10000;
int M = 0,N = 0;
int max_cost = 0;
long sum_cost = 0;
int day_cost[MAX_N] = {0};
bool readFromFile = false;

int main()
{
    //init
    if(!Init())
        return -1;

    //search
    int l,r;
    l = max_cost;
    r = sum_cost;
    //cout << "left = " << l << ", right = " << r << endl;
    int result = SearchMinCost(l,r);

    //output
    cout << result;

    return 0;
}

bool Init()
{
    /// input data
    if(readFromFile)
    {
        ifstream in("in.txt",ios::in);

        in >>N >> M;
        if(!(1 <= M  && M <= N && N <= MAX_N))
            return false;
        for(int i = 0;i<N;i++)
        {
            in >> day_cost[i];
            if(!(1 <= day_cost[i] && day_cost[i] <= MAX_DAY_COST))
                return false;
            if(max_cost < day_cost[i])
                max_cost = day_cost[i];
            sum_cost += day_cost[i];
        }
        return true;
    }

    cin >> N >> M;
    if(!(1 <= M  && M <= N && N <= MAX_N))
        return false;
    for(int i = 0;i<N;i++)
    {
        cin >> day_cost[i];
        if(!(1 <= day_cost[i] && day_cost[i] <= MAX_DAY_COST))
            return false;
        if(max_cost < day_cost[i])
            max_cost = day_cost[i];
        sum_cost += day_cost[i];
    }

}

int SearchMinCost(int left,int right)
{
    /// Binary search

    //init
    int mid = (left + right) / 2;
    int result = -1;

    //short circuit
    if(IsCostFeasible(left))
        return left;

    //binary search
    while(right - left >= 0)
    {
        if(IsCostFeasible(mid))
        {
            result = mid;
            right = mid - 1;
            //cout << mid <<" succeeded" << endl;
        }
        else
        {
            left = mid + 1;
            //cout << mid <<" failed" << endl;
        }
        mid = (left + right) / 2;
    }

    return result;
}

bool IsCostFeasible(int cost)
{
    //simple greedy algorithm

    //short circuit
    if(cost < max_cost)
        return false;

    //init
    int sum = 0, restMonth = M - 1;
    for(int i = 0;i < N ;i++)
    {
        if(sum + day_cost[i] <= cost)
            sum += day_cost[i];
        else
        {
            sum = day_cost[i];
            restMonth--;
        }
        //cout << "sum = " << sum << ", cost: " << cost << ", rest month: " << restMonth << endl;
        if(restMonth < 0)
            return false;
    }

    return 0 <= restMonth;
}
