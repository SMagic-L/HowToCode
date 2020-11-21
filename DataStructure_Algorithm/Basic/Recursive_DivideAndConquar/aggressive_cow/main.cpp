#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

//global
const int MAX_N = 100000;
const int MAX_STALL = 1000000000;
int N = 0,C = 1;
int stall[MAX_N] = {0};

//prototype
bool IsDOK(int D);
int SearchLargestMinDistance(int left, int right);
int cmpInt(const void * a, const void * b);
void Init();

int main()
{
    Init();
    int L = 1, R = (stall[N-1] - stall[0]) / (C - 1);
    int result = SearchLargestMinDistance(L, R);
    cout << result;

    return 0;
}

void Init()
{
    //input boundary data
    cin >> N >> C;

    //error check
    if(N > MAX_N || N < C || C < 2)
    {
        cout << "Input error! Out of range." << endl;
        exit(-1);
    }

    //input stall data and sort it
    for(int i = 0;i<N;i++)
    {
        scanf_s("%d",&stall[i]);
        if(stall[i] > MAX_STALL || stall[i] < 0)
        {
            cout << "Input error! Out of range." << endl;
            exit(-1);
        }
    }

    qsort(stall, N, sizeof(int), cmpInt);
}


int SearchLargestMinDistance(int left, int right)
{
    //init
    int mid = (left + right) / 2;
    int result = 0;

    //binary search
    while(right - left >= 0)
    {
        if(IsDOK(mid))
        {
            left = mid + 1;
            result = mid;
        }
        else
        {
            right = mid - 1;
        }
        mid = (left + right) / 2;
    }

    return result;
}

bool IsDOK(int D)
{
    //init
    int i = 0,p = stall[0];
    int restCow = C - 1;

    for(i = 1;i<N;i++)
    {
        if(stall[i] >= p + D)
        {
            p = stall[i];
            restCow--;
        }
    }

    return restCow <= 0;
}

int cmpInt(const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}
