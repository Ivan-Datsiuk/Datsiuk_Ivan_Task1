#include <iostream>
#include <chrono>   
#include <future>   
#include <algorithm>
#include <ctime>
#include <string>
#include <limits> 

using namespace std;
using namespace std::chrono;

void printArray(int arr[], int n, string msg);
void generateArray(int arr[], int n);
void insertionSort(int array[], int n);
void selectionSort(int array[], int n);
void quickSort(int array[], int left, int right);
int binSearch(int M[], int N, int x);
int getValidInput(string prompt);

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	int n, choice;

	while (true)
	{
		cout << "\n--- MENU ---" << endl;
		n = getValidInput("Enter array size (e.g. 12, 125, 1500, 7000, 35000, 170000..) or 0 to exit: ");

		if (n == 0) break;
		if (n < 0)
		{
			cout << "Size cannot be negative!" << endl;
			continue;
		}

		int* arrS = new int[n];
		int* arrA = new int[n];
		generateArray(arrS, n);
		for (int i = 0; i < n; i++) arrA[i] = arrS[i];

		printArray(arrS, n, "Original Array");

		while (true)
		{
			choice = getValidInput("Choose method: 1-Insertion, 2-Selection, 3-Quick: ");
			if (choice >= 1 && choice <= 3) break;
			cout << "Invalid choice! Please enter 1, 2 or 3." << endl;
		}

		auto s_start = high_resolution_clock::now();
		switch (choice)
		{
		case 1: insertionSort(arrS, n); break;
		case 2: selectionSort(arrS, n); break;
		case 3: quickSort(arrS, 0, n - 1); break;
		}
		auto s_stop = high_resolution_clock::now();
		cout << "Sync Time: " << duration_cast<microseconds>(s_stop - s_start).count() << " mks" << endl;

		auto a_start = high_resolution_clock::now();
		future<void> result;
		switch (choice)
		{
		case 1: result = async(launch::async, insertionSort, arrA, n); break;
		case 2: result = async(launch::async, selectionSort, arrA, n); break;
		case 3: result = async(launch::async, quickSort, arrA, 0, n - 1); break;
		}
		result.get();
		auto a_stop = high_resolution_clock::now();
		cout << "Async Time: " << duration_cast<microseconds>(a_stop - a_start).count() << " mks" << endl;

		printArray(arrS, n, "Sorted Array");

		int x = getValidInput("\nEnter key to find ALL indexes: ");
		int firstFound = binSearch(arrS, n, x);

		if (firstFound == -1)
		{
			cout << "Not found!" << endl;
		}
		else
		{
			cout << "Found at indexes: ";
			int i = firstFound;
			while (i > 0 && arrS[i - 1] == x) i--;
			while (i < n && arrS[i] == x) cout << i++ << " ";
			cout << endl;
		}

		delete[] arrS;
		delete[] arrA;
	}
	return 0;
}
int binSearch(int M[], int N, int x)
{
	int L = 0;
	int R = N - 1;

	while (L <= R)
	{
		int m = L + (R - L) / 2;
		if (M[m] == x)
		{
			return m;
		}
		if (M[m] < x)
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	}
	return -1;
}

int getValidInput(string prompt)
{
	int value;
	while (true)
	{
		cout << prompt;
		cin >> value;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error: Invalid input." << endl;
		}
		else return value;
	}
}

void printArray(int arr[], int n, string msg)
{
	cout << msg << ": ";
	if (n <= 10)
	{
		for (int i = 0; i < n; i++) cout << arr[i] << " ";
	}
	else
	{
		for (int i = 0; i < 5; i++) cout << arr[i] << " ";
		cout << "... [skipped " << (n - 10) << " elements] ... ";
		for (int i = n - 5; i < n; i++) cout << arr[i] << " ";
	}
	cout << endl;
}

void generateArray(int arr[], int n)
{
	for (int i = 0; i < n; i++) arr[i] = rand() % 1000;
}

void insertionSort(int array[], int n)
{
	for (int index = 1; index < n; index++)
	{
		int currentValue = array[index], position = index;
		while (position > 0 && array[position - 1] > currentValue)
		{
			array[position] = array[position - 1];
			position--;
		}
		array[position] = currentValue;
	}
}

void selectionSort(int array[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int minPos = i;
		for (int j = i + 1; j < n; j++)
		{
			if (array[j] < array[minPos]) minPos = j;
		}
		if (minPos != i)
		{
			int temp = array[i];
			array[i] = array[minPos];
			array[minPos] = temp;
		}
	}
}

void quickSort(int array[], int left, int right)
{
	int i = left, j = right, pivot = array[left + (right - left) / 2];
	while (i <= j)
	{
		while (array[i] < pivot) i++;
		while (array[j] > pivot) j--;
		if (i <= j)
		{
			int temp = array[i];
			array[i] = array[j];
			array[j] = temp;
			i++; j--;
		}
	}
	if (left < j) quickSort(array, left, j);
	if (i < right) quickSort(array, i, right);
}