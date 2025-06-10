#include "average.h"
#include <stdio.h>

int main(int argc, char *argv[])
{

	int arr[] = {010, 02, -100};
	int size = sizeof(arr) / sizeof(arr[0]);

	double result = average(arr, size);

	printf("Average: %.2f\n", result);

	return 0;
}