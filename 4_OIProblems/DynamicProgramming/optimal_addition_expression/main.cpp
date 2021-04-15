#include <iostream>
#include <cstring>
#include <algorithm>
#define INF_DATA "999999999999999999999999999999999999999999999999999"
using namespace std;

//global const
const int MAX_N = 52;

//struct
typedef struct
{
    char data[MAX_N];
} BigInt;

//global variable
BigInt subInt[MAX_N][MAX_N];
BigInt dp[MAX_N][MAX_N + 1];

//prototype
BigInt solveOptAddExp(int m, BigInt bigInt);
void setSubInt(BigInt bigInt);
int cmpBigInt(BigInt left, BigInt right);
BigInt getTmpMin(int m, int n);
BigInt bigPlus(BigInt left, BigInt right);

int main()
{
    //init
    int m = 0;
    BigInt result, input;
    memset(&input,0, sizeof(BigInt));

    while(cin >> m >> input.data)
    {
        //init and input
        memset(&dp, 0, sizeof(BigInt) * MAX_N * MAX_N);
        memset(&subInt, 0, sizeof(BigInt) * MAX_N * MAX_N);
        setSubInt(input);

        //get result
        result = solveOptAddExp(m, input);
        cout << result.data << endl;
    }

    return 0;
}

//Dynamic Programming

BigInt solveOptAddExp(int m, BigInt bigInt)
{
    //init
    int n = strlen(bigInt.data);
    BigInt tmpMin;

    //set initial dp
    for(int j = 1;j<= n;j++)
    {
        dp[0][j] = subInt[0][j-1];
    }

    //start rolling dp
    for(int i = 1;i <= m;i++)
    {
        for(int j = i + 1; j <= n; j++)
        {
            tmpMin = getTmpMin(i,j);
            dp[i][j] = bigPlus(tmpMin,dp[i][j]);
        }
    }

    return dp[m][n];
}

BigInt getTmpMin(int m, int n)
{
    //init
    BigInt result = {.data = INF_DATA},tmp;

    for(int j = m;j<n;j++)
    {
        tmp = bigPlus(dp[m-1][j],subInt[j][n-1]);
        if(cmpBigInt(tmp,result) < 0)
            result = tmp;
    }

    return result;
}

void setSubInt(BigInt bigInt)
{
    //init
    BigInt tmp;
    memset(&tmp,0, sizeof(BigInt));
    int n = strlen(bigInt.data);

    //set sub int
    for(int i = 0;i < n;i++)
    {
        memset(&tmp,0, sizeof(BigInt));
        for(int j = i;j < n;j++)
        {
            tmp.data[j-i] = bigInt.data[j];
            tmp.data[j-i+1] = '\0';
            subInt[i][j] = tmp;
        }
    }
}

//Accurate Calculation

int cmpBigInt(BigInt left, BigInt right)
{
    //init
    int len_L = strlen(left.data),len_R = strlen(right.data);

    //judge by length
    if(len_L != len_R)
        return len_L - len_R;

    //compare every bit
    for (int i = 0; i < len_L; ++i)
    {
        if(left.data[i] == right.data[i])
            continue;
        return left.data[i] - right.data[i];
    }

    return 0;
}

BigInt bigPlus(BigInt left, BigInt right)
{
    //init
    BigInt result;
    memset(&result,0, sizeof(BigInt));
    char tmp = 0;
    int a,b;
    int len_L = strlen(left.data),len_R = strlen(right.data);
    int len = max(len_L,len_R) + 1;
    result.data[len] = '\0';

    //plus
    for(int i = 1; i <= max(len_L,len_R); i++)
    {
        a = (len_L - i >= 0) ? (left.data[len_L - i] - '0') : 0;
        b = (len_R - i >= 0) ? (right.data[len_R - i] - '0') : 0;
        tmp = a + b;


        result.data[len-i] += tmp;
        if(result.data[len-i] >= 10)
        {
            result.data[len-i-1] += (result.data[len-i] / 10);
            result.data[len-i] %= 10;
        }
        result.data[len-i] += '0';
    }

    if(0 == result.data[0])
    {
        for(int i = 0; i < len;i++)
            result.data[i] = result.data[i+1];
    }
    else
        result.data[0] += '0';

    return result;
}







