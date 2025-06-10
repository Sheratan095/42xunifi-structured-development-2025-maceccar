// elements must be in range 0-100 inclusive
float	average(const int *arr, int size)
{
	int	sum = 0;
	int	valid_count = 0;

	if (size <= 0)
		return 0.0;

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
