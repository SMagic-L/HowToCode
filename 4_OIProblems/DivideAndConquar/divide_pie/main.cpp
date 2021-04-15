#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <cmath>

//prototype
bool Init();
double SearchMaxPie(double left, double right);
bool IsPieDividable(double square);
int compareFunction(const void * a, const void * b);
int GetIndexDividedBy(double square);

//global
const int PIE_HEIGHT = 1;
const double PI = acos(-1);
const int MAX_R = 10000;
const int MAX_F = 10000;
const int MAX_N = 10000;
int N = 0,F = 0;
int r2[MAX_N + 1] = {0};
long sum_r2 = 0;
bool readFromFile = false;

using namespace std;

int main()
{
    //init and check input
    if(!Init())
        return -1;
    double max_square,s1,s2,l,r;

    //binary search
    l = PI * r2[N-1] / (F+1);

    r = PI * r2[0];
    s1 = SearchMaxPie(l, r);
    r = PI * double(sum_r2) / (F+1);
    s2 = SearchMaxPie(l, r);

    max_square = fmax(s1,s2);

    //output max square;
    cout << setiosflags(ios::fixed) << setprecision(3) << max_square * PIE_HEIGHT;
    return 0;
}

bool Init()
{
    if(readFromFile)
    {
        ifstream in("in.txt",ios::in);
        if (! in.is_open())
        { cout << "Error opening file"; exit (1); }

        in >> N >> F;
        for(int i = 0;i < N;i++)
        {
            in >> r2[i];
            r2[i] *= r2[i];
            sum_r2 += r2[i];
        }

        //sort
        qsort(r2,N, sizeof(int),compareFunction);

        return true;
    }

    //N F
    cin >> N >> F;
    if(N < 1 || N > MAX_N || F <= 0 || F > MAX_F)
    {
        cout << "N F Input error!" << endl;
        return false;
    }

    //radius
    for(int i = 0;i<N;i++)
    {
        cin >> r2[i];
        if(r2[i] < 1 || r2[i] > MAX_R)
        {
            cout << "Radius Input error!  " << r2[i] << endl;
            return false;
        }
        r2[i] *= r2[i];
        sum_r2 += r2[i];
    }

    //sort
    qsort(r2,N, sizeof(int),compareFunction);

    return true;
}

double SearchMaxPie(double left, double right)
{
    //init
    double mid = (left + right) / 2;
    double result = 0.0;
    const double MIN_DELTA = 1e-5;

    //short circuit
    if(IsPieDividable(right))
        return right;
    if(0 == right - left)
        if(IsPieDividable(mid))
            {result = mid;}

    //binary search
    while(right - left >= MIN_DELTA)
    {
        if(IsPieDividable(mid))
        {
            left = mid;
            result = mid;
            //cout << mid << " succeeded" << endl;
        }
        else
        {
            right = mid;
            //cout <<mid << " failed" << endl;
        }
        mid = (left + right) / 2;
    }
    return result;
}

bool IsPieDividable(double square)
{
    int round = int(PI * r2[0] / square);
    int restPeople = F+1;
    for(int k = 1; k <= round;k++)
    {
        restPeople -= GetIndexDividedBy(k * square);
        if(restPeople <= 0)
            return true;
    }

    return restPeople <= 0;
}

int compareFunction(const void * a, const void * b)
{
    return -( *(int*)a - *(int*)b );
}

int GetIndexDividedBy(double square)
{
    ///return index of the first item lower than square

    //short circuit
    if(square <= PI * r2[N-1])
        return N;
    if(square > PI * r2[0])
        return -1;

    //init
    int a = 0,b = N-1,result = -1;
    int mid = (a+b) / 2;

    //binary search
    while(b-a >= 0)
    {
        if(PI * r2[mid] >= square)
        {
            result = mid;
            a = mid + 1;
        }
        else
        {
            b = mid - 1;
        }
        mid = (a + b) / 2;
    }

    return result + 1;
}