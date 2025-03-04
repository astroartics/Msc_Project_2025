#include "Matrix_Minors.hpp"

using namespace std;

int main()
{
    Matrix_Minors obj;

    obj.n = 6;
    obj.r = 3;

    obj.createMatrix();

    int possibleInd[obj.n];
    for (int i = 0; i < obj.n; i++)
        possibleInd[i] = i;

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

    int result[obj.r];

    cout << "kth combination : ";
    obj.get_kth_combination(possibleInd, obj.n, obj.r, 9, result);
    for (int i = 0; i < 3; i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;
}
