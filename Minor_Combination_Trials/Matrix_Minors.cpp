#include "Matrix_Minors.hpp"

using namespace std;
using namespace NTL;

Matrix_Minors::Matrix_Minors()
{
    n = 0;
    r = 0;
    zeroMinorCnt = 0;
}

mat_ZZ_p Matrix_Minors::createMatrix()
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

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    return mat;
}

void Matrix_Minors::output(int M[])
{
    for (int i = 0; i < r; i++)
    {
        cout << M[i] << " ";
    }
    cout << endl;
}

bool Matrix_Minors::isLast(const int (&M)[])
{
    int mSize = r;

    for (int i = mSize - 1, j = n - 1; i >= 0; i--, j--) // Checking if each element on a specific position has reached its end, i.e no element can be incremented further.
    {
        if (M[i] != j) // For example, for a 5x5 matrix and 3x3 minor, 4 will be the last element at the index 2 of 3x3 minor, 3 will be the last element at the index 1, and '2 3 4' will be the last combination.
            return false;
    }

    return true;
}

bool Matrix_Minors::getNextMinor(int (&M)[])
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

void Matrix_Minors::getMinors(const int M[])
{
    mat_ZZ_p minor;
    minor.SetDims(r, r);

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < r; j++)
        {
            // cout << "here" << endl;
            minor[i][j] = mat[M[i]][M[j]];
            cout << minor[i][j] << "\t";
        }
        cout << endl;
    }

    ZZ_p det = determinant(minor);
    if (det == ZZ_p(0))
        zeroMinorCnt++;

    cout << endl;
}

bool Matrix_Minors::get_kth_combination(int vec[], int n, int r, int index, int result_vec[])
{
    const int vec_len = n;
    const int result_vec_len = r;

    if (r < 0 || r > n)
    {
        cerr << "\n get_kth_combination :: Value error : invalid value of r :: " << r << endl;
        return false;
    }
    // ZZ c = conv<ZZ>("1");
    int c = 1;
    int k = r < (n - r) ? r : (n - r); //    min(r, n - r);

    for (int i = 1; i < k + 1; ++i)
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

    int result_vec_cnt = 0;
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