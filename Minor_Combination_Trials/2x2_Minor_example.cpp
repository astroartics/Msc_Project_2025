// Problem in this approach : As the minor dimensions will increase, more 'for' loops will have to be added, hence the program is not generalized for (n-1)x(n-1) minors for a nxn matrix.

#include <bits/stdc++.h>
#include <NTL/ZZ.h>
#include <NTL/mat_ZZ_p.h>
#define MATSIZE 10

using namespace std;
using namespace NTL;

int main()
{
    ZZ p;
    p = 32749;
    ZZ_p::init(p);
    int minorCount = 0, zeroMinorCount = 0;
    // vector<vector<int>> mat = {{1, 2, 3, 4, 5, 6}, {5, 6, 7, 8, 9, 10}, {9, 10, 11, 12, 13, 14}, {1, 2, 3, 4, 5, 8}, {5, 6, 7, 8, 9, 7}, {9, 10, 11, 12, 13, 14}};
    mat_ZZ_p mat, minor;
    mat.SetDims(MATSIZE, MATSIZE);
    minor.SetDims(2, 2);

    for (int i = 0; i < MATSIZE; i++)
    {
        for (int j = 0; j < MATSIZE; j++)
        {
            mat[i][j] = conv<ZZ_p>(RandomBits_ZZ(32749));
        }
    }

    // for (int i = 0; i < MATSIZE; i++)
    // {
    //     for (int j = 0; j < MATSIZE; j++)
    //     {
    //         cout << mat[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    for (int i = 0, a = 0; i < MATSIZE - 1; i++)
    {
        for (int j = i + 1; j < MATSIZE; j++)
        {
            for (int m = 0, b = 0; m < MATSIZE - 1; m++)
            {
                for (int n = m + 1; n < MATSIZE; n++)
                {
                    // cout << mat[i][m] << " " << mat[i][n] << endl;
                    // cout << mat[j][m] << " " << mat[j][n] << "\n\n";
                    minorCount++;
                    minor[0][0] = mat[i][m];
                    minor[0][1] = mat[i][n];
                    minor[1][0] = mat[j][m];
                    minor[1][1] = mat[j][n];

                    ZZ_p det = determinant(minor);
                    if (det == ZZ_p(0))
                        zeroMinorCount++;
                }
            }
        }
    }

    cout << "\nZero minor count : " << zeroMinorCount << "\n";
    cout << "Count of 2x2 minors : " << minorCount << "\n\n";
    return 0;
}