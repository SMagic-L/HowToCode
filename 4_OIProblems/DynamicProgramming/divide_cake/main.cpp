#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

//global
const int MAX_N = 21;
const int INF = 9999;
int dp[MAX_N][MAX_N][MAX_N];

//prototype
int divideCake(int w, int h, int m);
int getSV(int w, int h, int m);
int getSH(int w, int h, int m);

int main()
{
    //init
    int w = 0,h = 0,m = 0, result;
    memset(&dp,-1, sizeof(int) * MAX_N * MAX_N * MAX_N);

    //input
    while(true)
    {
        cin >> w >> h >> m;
        if(0 == w && 0 == h && 0 == m)
            break;
        result = divideCake(w,h,m-1);
        cout << result << endl;
    }

    return 0;
}

int divideCake(int w, int h, int m)
{
    //bound condition
    if(0 == m)
        return w*h;
    if(w * h < m + 1)
        return INF;
    if(-1 != dp[w][h][m])
        return dp[w][h][m];

    //init
    int sv = 0,sh = 0;
    sv = getSV(w,h,m-1);
    sh = getSH(w,h,m-1);
    dp[w][h][m] = min(sv,sh);
    return dp[w][h][m];
}

int getSH(int w, int h, int m)
{
    int s = INF,tmp_s = 0,result = INF;
    for(int j = 1;j< h;j++)
    {
        for(int k = 0;k<=m;k++)
        {
            tmp_s = max(divideCake(w,j,k),divideCake(w,h-j,m-k));
            if(tmp_s < s)
                s = tmp_s;
        }
        if(s < result)
            result = s;
    }
    return result;
}

int getSV(int w, int h, int m)
{
    int s = INF,tmp_s = 0,result = INF;
    for(int i = 1;i < w;i++)
    {
        for(int k = 0;k<= m;k++)
        {
            tmp_s = max(divideCake(i,h,k),divideCake(w-i,h,m-k));
            if(tmp_s < s)
                s = tmp_s;
        }
        if(s < result)
            result = s;
    }

    return result;
}
