#include <bits/stdc++.h>
#include <NTL/ZZ.h>
#include <NTL/mat_ZZ_p.h>

using namespace std;
using namespace NTL;

long int nCr(int n, int r)
{
    long int numerator = 1, denominator = 1;
    for (int i = n; i > (n - r); i--)
    {
        numerator *= i;
    }
    for (int i = r; i >= 1; i--)
    {
        denominator *= i;
    }

    long int result = (numerator / denominator);
    return result;
}

void displayMat(mat_ZZ_p &mat)
{
    long int n = mat.NumRows();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

void createMatrix(mat_ZZ_p &mat)
{
    long int n = mat.NumRows();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            mat[i][j] = conv<ZZ_p>(RandomBits_ZZ(32749));
        }
    }
}

bool get_kth_combination(long int vec[], long int n, long int r, long int index, long int result_vec[])
{
    const int vec_len = n;
    const int result_vec_len = r;

    if (r < 0 || r > n)
    {
        cerr << "\n get_kth_combination :: Value error : invalid value of r :: " << r << endl;
        return false;
    }
    // ZZ c = conv<ZZ>("1");
    long int c = 1;
    long int k = r < (n - r) ? r : (n - r); //    min(r, n - r);

    for (long int i = 1; i < k + 1; ++i)
    {
        // c = c * conv<ZZ>(floor((n - k + i)));
        c = c * (floor((n - k + i)));
        c = c / (i);
    }

    if (index < 0)
        index += c;

    if (index < 0 || index >= c)
    {
        cerr << "\n get_kth_combination :: Index error : invalid value for index :: " << index << endl;
        return false;
    }

    long int result_vec_cnt = 0;
    while (r)
    {
        c = (c * r) / n;
        n = n - 1;
        r = r - 1;

        while (index >= c)
        {
            index -= c;
            c = c * (n - r) / n;
            n = n - 1;
        }

        result_vec[result_vec_cnt] = vec[vec_len - n - 1];
        ++result_vec_cnt;
    }

    return true;
}

void getMinors(long int combinations[], long int combinationCount, int n, int r)
{
    long int col[r], row[r];
    long int minorCount = 0;

    for (int combinationNumber1 = 0; combinationNumber1 < combinationCount; combinationNumber1++)
    {
        get_kth_combination(combinations, n, r, combinationNumber1, row);
        for (int combinationNumber2 = 0; combinationNumber2 < combinationCount; combinationNumber2++)
        {
            get_kth_combination(combinations, n, r, combinationNumber2, col);
            for (int i = 0; i < r; i++)
            {
                for (int j = 0; j < r; j++)
                {
                    cout << row[i] << col[j] << " ";
                }
                cout << endl;
            }
            cout << endl;
            minorCount++;
        }
    }

    cout << endl
         << "Minor count : " << minorCount << endl;
}

int main()
{
    long int n = 3;
    long int r = 2;
    long int combinations[n];
    long int result[r];
    long int combinationCount = nCr(n, r);

    for (int i = 0; i < n; i++)
    {
        combinations[i] = i;
    }

    ZZ p;
    p = 32749;
    ZZ_p::init(p);

    mat_ZZ_p mat;
    mat.SetDims(n, n);
    createMatrix(mat);
    displayMat(mat);

    getMinors(combinations, combinationCount, n, r);

    // for (int combinationNumber = 0; combinationNumber < combinationCount; combinationNumber++)
    // {
    //     get_kth_combination(combinations, n, r, combinationNumber, result);
    //     getMinorCount(combinations, combinationCount, n, r, result);
    // }
}
