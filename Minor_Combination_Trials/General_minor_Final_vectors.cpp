#include <bits/stdc++.h>
#include <iterator>
#include <vector>
// #define SIZE 5
// #define MINORSIZE 3

using namespace std;

void output(vector<int> minorInd)
{
    for (int i = 0; i < minorInd.size(); i++)
    {
        cout << minorInd[i] << " ";
    }
    cout << endl;
}

bool isLast_1(const vector<int> &vec, int n)
{
    int sz = vec.size();

    for (int i = sz - 1, j = n - 1; i >= 0; --i, --j)
    {
        if (vec[i] != j)
            return false;
    }

    return true;
}

bool getNextMinor(vector<int> &minorInd, int n, int r)
{
    if (isLast_1(minorInd, n))
        return false;

    int sz = minorInd.size();

    if (minorInd[sz - 1] != n - 1)
    {
        minorInd[sz - 1]++;
        return true;
    }

    for (int i = sz - 2, j = 2; i >= 0; --i, ++j)
    {
        if (minorInd[i] != n - j)
        {
            minorInd[i]++;

            for (int k = i + 1; k <= sz - 1; ++k)
                minorInd[k] = minorInd[k - 1] + 1;

            return true;
        }
    }

    return false;
}

int main()
{
    int n = 12;
    int r = 4;
    vector<int> minorInd(r);
    for (int i = 0; i < r; i++)
        minorInd[i] = i;

    // minor(minorInd, n, r);

    int cnt(1);
    output(minorInd);
    while (getNextMinor(minorInd, n, r))
    {
        output(minorInd);
        ++cnt;
    }
    cout << "\n total combinations :: " << cnt << endl;
}

/*
int count = 0;

    output(M);
    count++;
    for (int i = M.size() - 2; i >= 0; i--)
    {
        while (M[M.size() - 1] < SIZE - 1)
        {
            for (int j = M.size() - 1; j > i; j--)
            {
                if (M[j] + 1 != SIZE)
                {
                    M[j]++;
                }
                output(M);
                count++;
            }
        }

        for (int m = 0; m < M.size(); m++)
        {
            M[m] = min[m];
        }

        M[i]++;

        for (int m = i + 1; m < M.size(); m++)
        {
            M[m] = M[m - 1] + 1;
        }
        output(M);
        count++;

        if (i == 0)
        {
            while (M[0] != (SIZE - MINORSIZE))
            {
                for (int j = M.size() - 1; j >= i; j--)
                {
                    if (M[j] + 1 != SIZE)
                    {
                        M[j]++;
                    }
                    output(M);
                    count++;
                    // if ((M[M.size() - 1] == SIZE - 1))
                    // {
                    //     j--;
                    // }
                }
            }
        }
    }
*/

/*


int isLast(vector<int> M, int n)
{
    if (M[M.size() - 1] < n)
    {
        return 1;
    }
    return 0;
}

int decrementI(vector<int> M, int i)
{
    int flag = 0;
    for (int n = i; n < M.size() - 1; n++)
    {
        if ((M[n + 1] - 1 != M[n]))
        {
            return 0;
        }
    }
    return 1;
}

vector<int> incrementIElements(vector<int> M, int i)
{
    for (int n = i + 1; n < M.size() - 1; n++)
    {
        M[n]++;
        output(M);
    }
    return M;
}

vector<int> resetMinor(vector<int> M, int j)
{
    for (int i = j + 1; i < M.size(); i++)
    {
        M[i] = M[i - 1] + 1;
    }
    return M;
}

void minor(vector<int> M, int n, int r)
{
    int cnt = 0;
    int j = M.size() - 1;

    while (M[0] <= (n - r))
    {
        for (int i = r - 1; i > 0;)
        {
            while (isLast(M, n))
            {
                output(M);
                cnt++;
                M[j]++;
            }

            if (i > 0 && (i < r - 1))
            {
                if (decrementI(M, i))
                {
                    i--;
                }
            }
            else if ((i == r - 1) && (M[r - 1] == n) && decrementI(M, i))
            {
                i--;
            }

            M[i]++;
            M = resetMinor(M, i);
        }
    }

    cout << "Combination count : " << cnt << endl;
}
*/