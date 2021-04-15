#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

//const
const int MAX_N = 51;

//global variable
int dp[MAX_N][MAX_N] = {0};

//prototype
int divideK(int n, int k);
void resetDp();
int divideOdd(int n, int h);
int divideDiff(int step, int sum, int n);

int main()
{
    int n,k,result = 0;
    while(cin >> n >> k)
    {
        resetDp();
        result = divideK(n - k, k);
        cout << result << endl;

        result = divideDiff(n, 0, n);
        cout << result << endl;

        resetDp();
        result = divideOdd(n, n);
        cout << result << endl;
    }

    return 0;
}

int divideOdd(int n, int h)
{
    //short circuit
    if(n < 0 || h < 0)
        return 0;
    if(-1 != dp[n][h])
        return dp[n][h];
    if(0 == h)
    {
        dp[n][h] = 0;
        return 0;
    }
    if(0 == n)
    {
        dp[n][h] = 1;
        return 1;
    }
    if(0 == h % 2)
    {
        dp[n][h] = divideOdd(n,h-1);
        return dp[n][h];
    }
    if(1 == h)
    {
        dp[n][h] = 1;
        return 1;
    }
    if(n < h)
    {
        dp[n][h] = divideOdd(n,n - 1 + (n % 2));
        return dp[n][h];
    }

    //normal recursive
    dp[n][h] = divideOdd(n-h,h) + divideOdd(n,h-2);
    return dp[n][h];
}

int divideDiff(int step, int sum, int n)
{
    if(step <= 0)
        return 0;
    if(n == sum + (n - step) + 1)
    {
        return 1;
    }
    if(n < sum + (n - step) + 1)
    {
        return 0;
    }
    int s = 0;
    s += divideDiff(step - 1, sum + (n - step) + 1, n);
    s += divideDiff(step - 1, sum, n);
    return s;
}

void resetDp()
{
    memset(&dp,-1, sizeof(int) * MAX_N * MAX_N);
}

int divideK(int n, int k)
{
    //short circuit
    if(n < 0 || k < 0)
        return 0;
    if(-1 != dp[n][k])
        return dp[n][k];
    if(0 == k)
    {
        dp[n][k] = 0;
        return 0;
    }
    if(0 == n)
    {
        dp[n][k] = 1;
        return 1;
    }

    //normal cursive
    if(n < k)
        dp[n][k] = divideK(n, n);
    else
        dp[n][k] = divideK(n - k, k) + divideK(n, k - 1);
    return dp[n][k];
}

