#include <iostream>
using namespace std;

const int MAX_K = 25;
int k = 0;
int height[MAX_K] = {0};
int maxFallingLength[MAX_K] = {0};

int maxCount();

int main()
{
    //init
    cin >> k;
    for(int i = 0;i <k;i++)
        cin >> height[i];

    int result = maxCount();

    cout  << result;
}

int maxCount()
{
    maxFallingLength[0] = 1;
    int tmpMax,result = 0;
    for(int i = 1;i < k;i++)
    {
        tmpMax = 0;
        //calc max falling length of current state
        for(int j = 0;j <i;j++)
        {
            if(height[j] < height[i])
                continue;
            if(maxFallingLength[j] > tmpMax)
                tmpMax = maxFallingLength[j];
        }
        maxFallingLength[i] = tmpMax + 1;
    }

    for(int i = 0;i < k;i++)
    {
        if(result < maxFallingLength[i])
            result = maxFallingLength[i];
    }

    return result;
}
