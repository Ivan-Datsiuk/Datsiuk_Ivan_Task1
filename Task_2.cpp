#include <iostream>
#include <cmath>   
#include <iomanip> 

using namespace std;

double calculateAverage(int arr[], int n);
double calculateDeviation(int arr[], int n, double average);
void printResults(double avg, double Dev);
int main() 
{
	const int n = 10;
	int X[n] = { 20, 11, 10, 19, 22, 23, 11, 18, 14, 25 };

	double avg = calculateAverage(X, n);
	double Dev = calculateDeviation(X, n, avg);

	printResults(avg, Dev);

	return 0;
}
double calculateAverage(int arr[], int n) 
{
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += arr[i];
	}
	return sum / n;
}
double calculateDeviation(int arr[], int n, double average)
{
	double sumSquares = 0;
	for (int i = 0; i < n; i++)
	{
		sumSquares += pow(arr[i], 2);
	}

	double term1 = (1.0 / (n - 1)) * sumSquares;
	double term2 = (static_cast<double>(n) / (n - 1)) * pow(average, 2);

	return sqrt(term1 - term2);
}
void printResults(double avg, double Dev) 
{
	cout << "Results:" << endl;
	cout << "Average (x_cp): " << fixed << setprecision(2) << avg << endl;
	cout << "Deviation (y): " << Dev << endl;
}