#include <iostream>
#include <mpi.h>
#include <stdlib.h>
#include <fstream>
#include <NTL/ZZ.h>
#include <NTL/mat_ZZ_p.h>
#include "Matrix_Minors.hpp"

using namespace std;
using namespace NTL;

int zeroMinorCnt = 0;

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

void createMatrix(mat_ZZ_p &mat, int n)
{
    mat.SetDims(n, n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            mat[i][j] = conv<ZZ_p>(RandomBits_ZZ(32749));
        }
    }
}

void displayMat(mat_ZZ_p &mat, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

void flattenMatrix(const mat_ZZ_p &mat, long int flattenedMat[])
{
    long int rows = mat.NumRows();
    long int cols = mat.NumCols();

    for (long int i = 0; i < rows; i++)
    {
        for (long int j = 0; j < cols; j++)
        {
            flattenedMat[i * cols + j] = conv<long int>(mat[i][j]);
        }
    }
}

void broadcastMatrix(mat_ZZ_p &mat, int rank, int n)
{
    if (rank == 0)
    {
        long int flatMat[n * n];
        flattenMatrix(mat, flatMat);
        MPI_Bcast(&n, 1, MPI_LONG, 0, MPI_COMM_WORLD);
        MPI_Bcast(flatMat, n * n, MPI_LONG, 0, MPI_COMM_WORLD);
    }
    else
    {
        long int flatMat[n * n];
        mat.SetDims(n, n);
        MPI_Bcast(&n, 1, MPI_LONG, 0, MPI_COMM_WORLD);
        MPI_Bcast(flatMat, n * n, MPI_LONG, 0, MPI_COMM_WORLD);
        for (long i = 0; i < n; ++i)
        {
            for (long j = 0; j < n; ++j)
            {
                mat[i][j] = flatMat[i * n + j];
            }
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

void getMinors(const long int M[], mat_ZZ_p &mat, int r)
{
    mat_ZZ_p minor;
    minor.SetDims(r, r);

    cout << "\n\n";
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
    cout << "\n\n";

    ZZ_p det = determinant(minor);
    if (det == ZZ_p(0))
        zeroMinorCnt++;
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    ZZ p;
    p = 32749;
    ZZ_p::init(p);
    mat_ZZ_p mat;
    long int n = 6, r = 3;
    long int combinations[n];

    if (world_rank == 0)
    {
        createMatrix(mat, n);
        displayMat(mat, n);
    }

    broadcastMatrix(mat, world_rank, n);

    MPI_Barrier(MPI_COMM_WORLD);
    // printf("Process %d received matrix:\n", world_rank);
    // for (long i = 0; i < n; ++i)
    // {
    //     for (long j = 0; j < n; ++j)
    //     {
    //         printf("%ld ", conv<long int>(mat[i][j]));
    //     }
    //     printf("\n");
    // }

    for (int i = 0; i < n; i++)
    {
        combinations[i] = i;
    }

    long int combinationCnt = nCr(n, r);
    long int ind = 0;
    long int minorIndRes[r];
    int index = (combinationCnt / world_size);

    if (world_rank != (world_size - 1))
    {
        for (ind = index * world_rank; ind < (index * (world_rank + 1)); ind++)
        {
            get_kth_combination(combinations, n, r, ind, minorIndRes);
            cout << "\nProcess ID : " << world_rank << endl;

            getMinors(minorIndRes, mat, r);
        }
        MPI_Bcast(&ind, 1, MPI_LONG, 0, MPI_COMM_WORLD);
    }

    MPI_Bcast(&ind, 1, MPI_LONG, 0, MPI_COMM_WORLD);
    if ((ind < combinationCnt) && (world_rank == (world_size - 1)))
    {
        for (ind = (index * (world_size - 1)); ind < combinationCnt; ind++)
        {
            get_kth_combination(combinations, n, r, ind, minorIndRes);
            cout << "\nProcess ID : " << world_rank << endl;

            getMinors(minorIndRes, mat, r);
        }
    }

    MPI_Finalize();
    return 0;
}

/*
            for (int k = 0; k < r; k++)
            {
                cout << endl
                     << minorIndRes[k] << " ";
            }
            cout << endl;
*/