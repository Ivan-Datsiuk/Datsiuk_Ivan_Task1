#include <iostream>
#include <ctime>

using namespace std;

void fillMatrix(int** matrix, int n);
void printMatrix(int** matrix, int n);
void task3Backslash(int** matrix, int n, int k);
void taskStar9(int** matrix, int n);
void deleteMatrix(int** matrix, int n);

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    int n, k;

    cout << "Enter n: ";
    cin >> n;

   int** matrix = new int* [n];
    for (int i = 0; i < n; i++) matrix[i] = new int[n];

    fillMatrix(matrix, n);
    cout << "\nMatrix: " << endl;
    printMatrix(matrix, n);

    cout << "\nEnter k: ";
    cin >> k;

    task3Backslash(matrix, n, k);
    taskStar9(matrix, n);

    cout << "\nNew matrix: " << endl;
    printMatrix(matrix, n);

    deleteMatrix(matrix, n);

    return 0;
}

void fillMatrix(int** matrix, int n) 
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = -20 + rand() % 41;
}

void printMatrix(int** matrix, int n) 
{
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) cout << matrix[i][j] << "\t";
        cout << endl;
    }
}

void task3Backslash(int** matrix, int n, int k) 
{
    int count = 0;
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            if (j >= i && (i + j >= n - 1)) 
            {
                if (matrix[i][j] < k) count++;
            }
        }
    }
    cout << "Number of elements in sector 3\ less than k: " << count << endl;
}

void taskStar9(int** matrix, int n) 
{
     int minDiag = matrix[0][0];
    for (int i = 1; i < n; i++)
        if (matrix[i][i] < minDiag) minDiag = matrix[i][i];
cout << "Minimum on diagonal: " << minDiag << endl;

    int count = 0;
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            if (i >= n / 2) 
            {
                count++;
                matrix[i][j] = minDiag;
            }
        }
    }
    cout << "Number of elements in sector 9: " << count << endl;
}

void deleteMatrix(int** matrix, int n) 
{
    for (int i = 0; i < n; i++) delete[] matrix[i];
    delete[] matrix;
}