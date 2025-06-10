#include "average.h"
#include <stdio.h>

int main(int argc, char *argv[])
{

	int arr[] = {1, 2, 100}; // Example array
	int size = sizeof(arr) / sizeof(arr[0]); // Calculate the size of the array

	double result = average(arr, size); // Call the average function

	// Print the result to standard output
	printf("Average: %.2f\n", result);

	return 0; // Return success code
}