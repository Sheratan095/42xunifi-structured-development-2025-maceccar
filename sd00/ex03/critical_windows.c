static int	check_window(const int *win_start, const int *win_end);

int	count_critical_windows(const int *readings, int size)
{
	int	count = 0;
	int	*win_start = (int *)readings;
	int	*win_end;

	if (size < 5)
		return 0; // Not enough readings to form a window

	for (int i = 0; i <= size - 5; i++)
	{
		win_end = (int *)(readings + i + 5);
		if (check_window(win_start, win_end))
		{
			count++;
		}
		win_start++;
	}
	
	return count; // Return the count of critical windows
}

// 1: Critical, 0: Non critical
static int	check_window(const int *win_start, const int *win_end)
{
	int	total = 0;//used to calculate the avarage
	int	critical_days = 0;//used to count the days with readings >= 70

	for (const int *ptr = win_start; ptr < win_end; ptr++)
	{
		if (*ptr >= 150)
			return 0;

		if (*ptr >= 70)
			critical_days++;

		total += *ptr;
	}

	if (total / (win_end - win_start) >= 90 && critical_days >= 3)
		return 1;

	return 0;
}