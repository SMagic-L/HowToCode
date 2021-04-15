#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

//struct
typedef struct
{
    int i;
    int j;
} State;

//global
const int MAX_LENGTH = 201;
int dp[MAX_LENGTH + 1][MAX_LENGTH + 1] = {0};
queue<State> q;

//prototype
bool isShortCircuitFeasible(char sub[], char origin[]);
void showResult(bool feasible, int i);
bool solve(char A[], char B[], const char C[]);
void resetDp(int m, int n);
bool isNeighborStateAvailable(State *st, int m, int n);
void addNeighborState(queue<State> *ptr_q, State *st);

int main()
{
    //init
    int n;
    cin >> n;
    char A[MAX_LENGTH] = "";
    char B[MAX_LENGTH] = "";
    char C[2 * MAX_LENGTH] = "";

    //calc
    for(int i = 1;i<= n;i++)
    {
        cin >> A >> B >> C;

        //short circuit
        if(!(isShortCircuitFeasible(A, C) && isShortCircuitFeasible(B, C)))
        {
            showResult(false, i);
            continue;
        }

        //dynamic programming
        showResult(solve(A, B, C), i);
    }
    return 0;
}

bool solve(char A[], char B[], const char C[])
{
    //init
    int len_A = strlen(A),len_B = strlen(B);
    resetDp(len_A, len_B);
    dp[len_A][len_B] = 1;
    State st = {.i = len_A,.j =  len_B};
    addNeighborState(&q, &st);

    //bfs
    while(!q.empty())
    {
        st = q.front();

        //DP: if state already judged, jump over
        if(-1 != dp[st.i][st.j] )
        {
            q.pop();
            continue;
        }

        //DP: use existing state to calc current state
        if(isNeighborStateAvailable(&st, len_A, len_B))
        {
            dp[st.i][st.j] = (dp[st.i + 1][st.j] || dp[st.i][st.j + 1]);
            if(1 == dp[st.i][st.j])
                addNeighborState(&q, &st);
            q.pop();
            continue;
        }

        //use given condition to judge state
        if(A[st.i] == C[st.i + st.j] || B[st.j] == C[st.i + st.j])
            dp[st.i][st.j] = 1;
        else
            dp[st.i][st.j] = 0;

        //add neighbor to queue
        if(1 == dp[st.i][st.j])
            addNeighborState(&q, &st);

        q.pop();
    }

    return 1 == dp[0][0];
}

void addNeighborState(queue<State> *ptr_q, State *st)
{
    if(st->i > 0)
    {
        st->i--;
        ptr_q->push(*st);
        st->i++;
    }
    if(st->j > 0)
    {
        st->j--;
        ptr_q->push(*st);
        st->j++;
    }
}

bool isNeighborStateAvailable(State *st, int m, int n)
{
    if(st->i >= m)
        return false;
    if(st->j >= n)
        return false;
    if(-1 == dp[st->i + 1][st->j])
        return false;
    return -1 != dp[st->i][st->j + 1];
}

void resetDp(int m, int n)
{
    for(int i = 0;i <= m; i++)
        for(int j = 0;j <= n; j++)
            dp[i][j] = -1;
}

void showResult(bool feasible, int i)
{
    cout << "Data set " << i << ": ";
    if(feasible)
        cout << "yes";
    else
        cout << "no";
    cout << endl;
}

bool isShortCircuitFeasible(char sub[], char origin[])
{
    int opt = 0;
    int str_len_sub = strlen(sub);
    int str_len_ori = strlen(origin);
    for(int i = 0;i<str_len_ori;i++)
    {
        if(origin[i] == sub[opt])
            opt++;
        if(opt == str_len_sub)
            return true;
    }
    return false;
}