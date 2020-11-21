#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

//struct
typedef struct {
    int weight;
    int value;
} Jewel;

//global
const int MAX_COUNT = 3402;
const int MAX_WEIGHT = 12881;
int dp[2][MAX_WEIGHT];
Jewel jewel[MAX_COUNT];

//prototype
int knapsack(int n, int m);

int main()
{
    //init
    int n,m;
    memset(&dp,0,sizeof(int) * MAX_WEIGHT * 2);
    memset(&jewel,0,sizeof(Jewel) * MAX_COUNT);
    cin >> n >> m;
    for(int i = 0; i < n;i++)
    {
        cin >> jewel[i].weight >> jewel[i].value;
    }

    int result = knapsack(n,m);

    cout << result;
    return 0;
}

int knapsack(int n, int m)
{
    //init knapsack
    for (int j2 = 0; j2 <= m; j2++)
    {
        if (j2 < jewel[0].weight)
        {
            dp[1][j2] = 0;
        } else
        {
            dp[1][j2] = jewel[0].value;
        }
    }

    for (int i = 1; i < n; i++)
    {
        for (int j1 = 0; j1 <= m; j1++)
        {
            dp[0][j1] = dp[1][j1];
        }
        for (int j = 0; j <= m; j++)
        {

            if (j < jewel[i].weight)
            {
                dp[1][j] = dp[0][j];
                continue;
            }
            dp[1][j] = max(dp[0][j], dp[0][j - jewel[i].weight] + jewel[i].value);
        }
    }

    return dp[1][m];
}

