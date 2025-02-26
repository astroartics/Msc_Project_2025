#include <bits/stdc++.h>
#include <iterator>
#include <vector>
#define SIZE 3
#define MINORSIZE 2

using namespace std;

bool isSorted(vector<int> arr)
{
    for (int i = 1; i < arr.size(); i++)
        if (arr[i - 1] > arr[i])
            return false;
    return true;
}

int main()
{
    int mat[SIZE][SIZE], num = 1;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            mat[i][j] = (num++);
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << "\n";
    }
    cout << endl;

    int arr[SIZE], index = 0;

    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = i; // Index numbers
    }

    int n = sizeof(arr) / sizeof(arr[0]);

    vector<vector<int>> minorIndices;

    // Generate all permutation of an array
    do
    {
        vector<int> sortedIndices;
        for (int i = 0; i < MINORSIZE; i++)
        {
            // cout << arr[i] << " ";
            sortedIndices.push_back(arr[i]);
        }

        sort(sortedIndices.begin(), sortedIndices.end());

        if (find(minorIndices.begin(), minorIndices.end(), sortedIndices) == minorIndices.end())
        {
            minorIndices.push_back(sortedIndices);
        }
        // cout << endl;
    } while (next_permutation(arr, arr + n));
    //.
    //.
    //.
    for (int i = 0; i < minorIndices.size(); i++)
    {
        for (int j = 0; j < minorIndices[0].size(); j++)
        {
            cout << minorIndices[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n\n";
    //.
    //.
    //.
    int cnt = 0;
    for (int m = 0; m < minorIndices.size(); m++)
    {
        for (int i = 0; i < minorIndices.size(); i++)
        {
            for (int j = 0; j < minorIndices[0].size(); j++)
            {
                for (int k = 0; k < minorIndices[0].size(); k++)
                {
                    int row = minorIndices[m][j];
                    int col = minorIndices[i][k];
                    cout << mat[row][col] << " ";
                }
                cout << endl;
            }
            cnt++;
            cout << endl;
        }
    }

    cout << "\nCount : " << cnt << endl;

    return 0;
}