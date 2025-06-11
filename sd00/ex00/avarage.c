// elements must be in range 0-100 inclusive
float	average(const int *arr, int size)
{
	int	sum = 0;
	int	valid_count = 0;

	for (int i = 0; i < size; i++)
	{
		if (arr[i] >= 0 && arr[i] <= 100)
		{
			sum += arr[i];
			valid_count++;
		}
	}

	if (valid_count == 0)
		return 0.0; // Avoid division by zero if no valid elements

	return ((float)sum / valid_count);
}








// #include "average.h"
// #include <stdio.h>

// int main(int argc, char *argv[])
// {

// 	int arr[] = {010, 02, -100};
// 	int size = sizeof(arr) / sizeof(arr[0]);

// 	double result = average(arr, size);

// 	printf("Average: %.2f\n", result);

// 	return 0;
// }