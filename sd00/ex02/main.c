
#include <stdio.h>
#include "segmented_runs.h"

int main(int argc, char *argv[])
{
	const int	arr[] = {2, 3, 4, -1, 5, 6, -1, 1, 2, 3, 4};
	int	size = sizeof(arr) / sizeof(arr[0]);

	int	result = count_segments(arr, size);
	printf("Number of segments with increasing sequences longer than 3: %d\n", result);

	return 0;
}