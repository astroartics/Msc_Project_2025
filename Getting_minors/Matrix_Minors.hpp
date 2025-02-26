#include <bits/stdc++.h>
#include <NTL/ZZ.h>
#include <NTL/mat_ZZ_p.h>

class Matrix_Minors
{
public:
    long int n, r, zeroMinorCnt;
    NTL::mat_ZZ_p mat;

    Matrix_Minors();
    NTL::mat_ZZ_p createMatrix();
    void output(int[]);
    bool isLast(const int (&M)[]);
    bool getNextMinor(int (&M)[]);
    void getMinors(const int[]);
    bool get_kth_combination(int[], int, int, int, int[]);
};