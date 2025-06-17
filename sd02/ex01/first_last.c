
//arr should be int * and instead of int[] for sonarQube
void	first_last(int arr[], int size, int target, int *first, int *last)
{
	*first = -1;
	*last = -1;

	for (int i = 0; i < size;  i++)
	{
		if (arr[i] == target)
		{
			if (*first == -1)//first occurrence
				*first = i;

			*last = i; //update last occurrence every time
		}
	}
}







// #include <stdio.h>
// #include "first_last.h"

// int main(int argc, char *argv[])
// {
// 	int arr[] = {1, 2, 3, 4, 5, 3, 6};
// 	int size = sizeof(arr) / sizeof(arr[0]);
// 	int target = 1;
// 	int first;
// 	int last;

// 	first_last(arr, size, target, &first, &last);

// 	if (first != -1 && last != -1) {
// 		printf("First occurrence of %d is at index %d\n", target, first);
// 		printf("Last occurrence of %d is at index %d\n", target, last);
// 	} else {
// 		printf("%d not found in the array.\n", target);
// 	}

// 	return 0;
// }