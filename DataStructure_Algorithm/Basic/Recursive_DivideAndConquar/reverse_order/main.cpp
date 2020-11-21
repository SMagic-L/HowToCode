#include <iostream>
using namespace std;

//prototype
void MergeSortAndCount(int left, int right);
void Merge(int left, int right);

//global
const int MAX_N = 100000;
int ori_data[MAX_N] = {0};
int backup_data[MAX_N] = {0};
int n = 0;
long long result = 0;

int main()
{
    //init
    cin >> n;
    for(int i = 0;i<n;i++)
        cin >> ori_data[i];

    MergeSortAndCount(0,n-1);

    cout << result << endl;
    return 0;
}

void MergeSortAndCount(int left, int right)
{
    if(right - left <= 0)
        return;
    int mid = left + (right - left) / 2;
    MergeSortAndCount(left,mid);
    MergeSortAndCount(mid + 1,right);
    Merge(left,right);
}

void Merge(int left, int right)
{
    //init
    int mid = left + (right - left) / 2;
    int i = left,j = mid + 1,k = left;

    //backup
    for(int index = left; index <= right; index++)
        backup_data[index] = ori_data[index];

    //count and merge
    while(!( i > mid && j > right))
    {
        if(i > mid)
        {
            ori_data[k++] = backup_data[j++];
            continue;
        }
        if(j > right)
        {
            ori_data[k++] = backup_data[i++];
            continue;
        }

        if(backup_data[i] > backup_data[j])
        {
            result += (right - j + 1);
            ori_data[k++] = backup_data[i++];
        }
        else
        {
            ori_data[k++] = backup_data[j++];
        }
    }

}
