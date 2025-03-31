#include <bits/stdc++.h>
#include <mpi.h>
#include <NTL/ZZ.h>
#include <NTL/mat_ZZ_p.h>

using namespace std;
using namespace NTL;

/*
mpic++ Parallel.cpp -o op -lntl -lmpi
mpirun op
*/

long int nCr(int n, int r)
{
    long int numerator = 1, denominator = 1;
    for (long int i = n; i > (n - r); i--)
    {
        numerator *= i;
    }
    for (long int i = r; i >= 1; i--)
    {
        denominator *= i;
    }

    long int result = (numerator / denominator);
    return result;
}

void displayMat(mat_ZZ_p &mat)
{
    long int n = mat.NumRows();

    for (long int i = 0; i < n; i++)
    {
        for (long int j = 0; j < n; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

void createMatrix(mat_ZZ_p &mat)
{
    long int n = mat.NumRows();

    for (long int i = 0; i < n; i++)
    {
        for (long int j = 0; j < n; j++)
        {
            mat[i][j] = conv<ZZ_p>(RandomBits_ZZ(32749));
        }
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

    long int c = 1;
    long int k = r < (n - r) ? r : (n - r); //    min(r, n - r);

    for (long int i = 1; i < k + 1; ++i)
    {
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

// Method that put a lot of load on the last processor
// void getMinors(long int combinations[], long int combinationCount, int n, int r, int world_rank, int world_size)
// {
//     long int col[r], row[r];
//     long int combinationCount = nCr(n, r);
//     long int blockSize = combinationCount / world_size;
//     long int start = world_rank * blockSize;
//     long int end = ((world_rank == world_size - 1) ? combinationCount : start + blockSize);

//     long int localMinorCount = 0; // Local count per process

//     for (long int combinationNumber1 = start; combinationNumber1 < end; combinationNumber1++)
//     {
//         get_kth_combination(combinations, n, r, combinationNumber1 % combinationCount, row);
//         for (long int combinationNumber2 = 0; combinationNumber2 < combinationCount; combinationNumber2++)
//         {
//             get_kth_combination(combinations, n, r, combinationNumber2, col);
//             for (long int i = 0; i < r; i++)
//             {
//                 for (long int j = 0; j < r; j++)
//                 {
//                     cout << row[i] << col[j] << " ";
//                 }
//                 cout << endl;
//             }
//             cout << endl;
//             localMinorCount++;
//         }
//     }

//     long int globalMinorCount = 0;
//     MPI_Reduce(&localMinorCount, &globalMinorCount, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

//     if (world_rank == 0)
//     {
//         cout << "\nTotal minors : " << globalMinorCount << endl;
//     }
// }

void minorDeterminant(long int r, long int row[], long int col[], mat_ZZ_p mat)
{
    mat_ZZ_p minor;
    minor.SetDims(r, r);

    for (long int i = 0; i < r; i++)
    {
        for (long int j = 0; j < r; j++)
        {
            minor[i][j] = mat[row[i]][col[j]];
            cout << minor[i][j] << " ";
        }
        cout << endl;
    }
    ZZ_p det = determinant(minor);
    cout << endl;
}

// Method that evenly distributes minor calculations among all processors, with the last processor doing slightly more work
void getMinors(long int combinations[], int n, int r, int world_rank, int world_size, mat_ZZ_p mat)
{
    long int col[r], row[r];
    long int combinationCount = nCr(n, r);
    long int totalCombinations = pow(combinationCount, 2);
    long int blockSize = totalCombinations / world_size;
    long int startRow = world_rank * blockSize / combinationCount;
    long int startCol = world_rank * blockSize % combinationCount;

    if ((totalCombinations < world_size) && world_rank < totalCombinations)
    {
        blockSize = 1;
        startRow = world_rank / combinationCount;
        startCol = world_rank % combinationCount;
    }

    if (world_rank == (world_size - 1) && (totalCombinations >= world_size))
    {
        long int excessRows = blockSize % world_size;
        blockSize += excessRows - 1;
    }

    long int count = 0;
    get_kth_combination(combinations, n, r, startRow, row);

    while (count < blockSize)
    {
        get_kth_combination(combinations, n, r, startCol, col);
        minorDeterminant(r, row, col, mat);

        startCol++;
        if (startCol == (n) && startRow < (n - 1))
        {
            startCol = 0;
            startRow++;
            get_kth_combination(combinations, n, r, startRow, row);
        }
        count++;
    }
    // cout << count << endl;
}

int main(int argc, char *argv[])
{
    long int n = 3;
    long int r = 2;
    long int combinations[n];
    long int combinationCount = nCr(n, r);

    for (int i = 0; i < n; i++)
    {
        combinations[i] = i;
    }

    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    ZZ p;
    p = 32749;
    ZZ_p::init(p);

    mat_ZZ_p mat;
    mat.SetDims(n, n);

    if (world_rank == 0)
    {
        createMatrix(mat);
        displayMat(mat);
        cout << endl;
    }

    broadcastMatrix(mat, world_rank, n);
    MPI_Barrier(MPI_COMM_WORLD);

    getMinors(combinations, n, r, world_rank, world_size, mat);

    MPI_Finalize();
}
