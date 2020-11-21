#include <iostream>
using std::cin;
using std::cout;
using std::endl;

//prototype
int compareFunction(const void * a, const void * b);
void SortTheData(int n);

//global
const int MAX_N = 100000;
int the_data[MAX_N] = {0};

int main()
{
    //init
    int n = 0,k = 0;
    cin >> n;
    for(int i = 0; i < n;i++)
        cin >> the_data[i];
    cin >> k;

    //sort
    SortTheData(n);

    //output
    for(int i = 0;i < k;i++)
        cout << the_data[i] << endl;

    return 0;
}

void SortTheData(int n)
{
    qsort(the_data, n, sizeof(int), compareFunction);
}

int compareFunction(const void * a, const void * b)
{
    return -( *(int*)a - *(int*)b );
}