#include <stdio.h>

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
				if (contains_increasign_run(&arr[subsequence_start], sequence_len) == 1)
					result++;
				subsequence_start = i + 1; // move to the next subsequence
			}
		}
	}

	return result;
}

// 1: TRUE, 0: FALSE
static int	contains_increasign_run(const int *subsequence, int size)
{
	int	in_streak = 1;
	int	i = 1;

	while (i < size)
	{
		if (subsequence[i] > subsequence[i - 1])
		{
			in_streak++;
			if (in_streak >= 3)
				return 1; // return early if we already have a valid sequence
		}
		else
		{
			in_streak = 1; // reset the streak if the sequence is not increasing
		}
		i++;
	}

	return 0; // return the length of the last increasing sequence
}