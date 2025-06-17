#include "segmented_runs.h"

static int	contains_increasign_run(const int *subsequence, int size);

int	count_segments(const int *arr, int size)
{
	int	result = 0;
	int	subsequence_start = 0;

	for (int i = 0; i <= size; i++)
	{
		// reach the end of a subsequence or the end of the array
		// this order of conditions is important to handle the last element
		//  beacasue, in case of i == size, arr[i] would cause a conditional jump
		if (i == size || arr[i] == -1)
		{
			int	sequence_len = i - subsequence_start;
			if (sequence_len > 0)
			{
				result += contains_increasign_run(&arr[subsequence_start], sequence_len);
				subsequence_start = i + 1; // move to the next subsequence
			}
		}
	}

	return result;
}

// 1: TRUE, 0: FALSE
static int	contains_increasign_run(const int *subsequence, int size)
{
	int		in_streak = 1;
	int		i = 1;
	bool	valid_sequence_found = false;

	while (i < size && valid_sequence_found == false)
	{
		if (subsequence[i] > subsequence[i - 1])
		{
			in_streak++;
			if (in_streak >= 3)
				valid_sequence_found = true; // return early if we already have a valid sequence
		}
		else
		{
			in_streak = 1; // reset the streak if the sequence is not increasing
		}
		i++;
	}

	return valid_sequence_found;
}







// #include <stdio.h>
// #include <assert.h>

// // Test helper function to print the test result
// void run_test(const int *arr, int size, int expected, const char *test_name)
// {
// 	int result = count_segments(arr, size);
// 	printf("Test: %s - ", test_name);
// 	if (result == expected) {
// 		printf("PASSED ✓ (Expected: %d, Got: %d)\n", expected, result);
// 	} else {
// 		printf("FAILED ✗ (Expected: %d, Got: %d)\n", expected, result);
// 	}
// }

// int main() {
// 	printf("Running tests for count_segments function:\n");
	
// 	// Test 1: Empty array
// 	{
// 		const int arr[] = {};
// 		run_test(arr, 0, 0, "Empty array");
// 	}
	
// 	// Test 2: Single element array
// 	{
// 		const int arr[] = {5};
// 		run_test(arr, 1, 0, "Single element array");
// 	}
	
// 	// Test 3: Two elements array (not enough for a run)
// 	{
// 		const int arr[] = {1, 2};
// 		run_test(arr, 2, 0, "Two elements array");
// 	}
	
// 	// Test 4: Three increasing elements (exactly enough for a run)
// 	{
// 		const int arr[] = {1, 2, 3};
// 		run_test(arr, 3, 1, "Three increasing elements");
// 	}
	
// 	// Test 5: Multiple segments with valid runs
// 	{
// 		const int arr[] = {2, 3, 4, -1, 5, 6, 7, -1, 1, 2, 3, 4};
// 		run_test(arr, 12, 3, "Multiple segments with valid runs");
// 	}
	
// 	// Test 6: No valid runs in any segment
// 	{
// 		const int arr[] = {3, 2, 1, -1, 6, 5, -1, 9, 8};
// 		run_test(arr, 9, 0, "No valid runs in any segment");
// 	}
	
// 	// Test 7: Some segments have valid runs, others don't
// 	{
// 		const int arr[] = {1, 2, 3, 4, -1, 5, 4, 3, -1, 7, 8, 9};
// 		run_test(arr, 12, 2, "Mixed segments");
// 	}
	
// 	// Test 8: Segments with exactly 3 increasing elements
// 	{
// 		const int arr[] = {1, 2, 3, -1, 4, 5, 6, -1, 7, 8, 9};
// 		run_test(arr, 11, 3, "Segments with exactly 3 increasing elements");
// 	}
	
// 	// Test 9: Non-consecutive increasing elements (should not count)
// 	{
// 		const int arr[] = {1, 3, 5, 7};
// 		run_test(arr, 4, 1, "Non-consecutive increasing elements");
// 	}
	
// 	// Test 10: Multiple valid runs within one segment
// 	{
// 		const int arr[] = {1, 2, 3, 2, 3, 4, 5};
// 		run_test(arr, 7, 1, "Multiple valid runs within one segment");
// 	}
	
// 	// Test 11: Edge case with consecutive -1 values
// 	{
// 		const int arr[] = {1, 2, 3, -1, -1, 4, 5, 6};
// 		run_test(arr, 8, 2, "Consecutive -1 values");
// 	}
	
// 	return 0;
// }
