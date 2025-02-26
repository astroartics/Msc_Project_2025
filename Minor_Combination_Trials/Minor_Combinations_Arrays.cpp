#include <bits/stdc++.h>
#include <NTL/ZZ.h>
#include <NTL/mat_ZZ_p.h>

using namespace std;
using namespace NTL;

class MinorCombinations
{
public:
    int n, r, zeroMinorCnt;
    mat_ZZ_p mat;

    MinorCombinations()
    {
        n = 0;
        r = 0;
        zeroMinorCnt = 0;
    }

    void createMatrix()
    {
        ZZ p;
        p = 32749;
        ZZ_p::init(p);

        mat.SetDims(n, n);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                mat[i][j] = conv<ZZ_p>(RandomBits_ZZ(32749));
            }
        }
    }

    void output(int M[])
    {
        for (int i = 0; i < r; i++)
        {
            cout << M[i] << " ";
        }
        cout << endl;
    }

    bool isLast(const int (&M)[])
    {
        int mSize = r;

        for (int i = mSize - 1, j = n - 1; i >= 0; i--, j--) // Checking if each element on a specific position has reached its end, i.e no element can be incremented further.
        {
            if (M[i] != j) // For example, for a 5x5 matrix and 3x3 minor, 4 will be the last element at the index 2 of 3x3 minor, 3 will be the last element at the index 1, and '2 3 4' will be the last combination.
                return false;
        }

        return true;
    }

    bool getNextMinor(int (&M)[])
    {
        if (isLast(M)) // Returning if the last combination is reached.
            return false;

        int mSize = r;

        if (M[mSize - 1] != n - 1) // Checking if the element on the last position can be incremented or not. Completely incrementing the element at last position till it reaches (n-1).
        {
            M[mSize - 1]++;
            return true;
        }

        for (int i = mSize - 2, j = 2; i >= 0; i--, j++) // Starting from the second last position and comparing if the element at that position has reached its end or not.
        {
            if (M[i] != n - j) // For example, (5x5 matrix and 3x3 minor) M[1] will go till 3, as M[2] i.e. the last element will go till 4.
            {
                M[i]++;

                for (int k = i + 1; k < mSize; k++) // Resetting the array starting from the (i+1)th position.
                    M[k] = M[k - 1] + 1;

                return true;
            }
        }

        return false;
    }

    void getMinors(const int M[])
    {
        mat_ZZ_p minor;
        minor.SetDims(r, r);

        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < r; j++)
            {
                // cout << "here" << endl;
                cout << mat[M[i]][M[j]] << "\t";
                minor[i][j] = mat[M[i]][M[j]];
            }
            cout << endl;
        }

        ZZ_p det = determinant(minor);
        if (det == ZZ_p(0))
            zeroMinorCnt++;

        cout << endl;
    }
};

int main()
{
    MinorCombinations obj;

    obj.n = 5;
    obj.r = 3;

    obj.createMatrix();

    int minorInd[obj.r];
    for (int i = 0; i < obj.r; i++)
        minorInd[i] = i;

    int cnt = 1;

    obj.getMinors(minorInd);
    while (obj.getNextMinor(minorInd))
    {
        cnt++;
        // obj.getMinors(minorInd);
        obj.output(minorInd);
    }

    cout << "\nTotal combinations : " << cnt << endl;
    cout << "\nZero minor count : " << obj.zeroMinorCnt << endl;
}

/*
Time difference

1) Using vectors :
real    0m0.772s
user    0m0.712s
sys     0m0.060s

2) Using arrays :
real    0m0.756s
user    0m0.679s
sys     0m0.077s
*/