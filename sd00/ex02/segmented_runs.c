
static int	get_increasing_sequence(const int *subsequence);

int	count_segments(const int *arr, int size)
{
}

static int	get_increasing_sequence(const int *subsequence)
{
	int	incresing_len = 0;
	int	last_element_in_subsequence = subsequence[0];
	int	i = 0;

	while (subsequence[i] && subsequence[i] != -1)
	{
		if (subsequence[i] > last_element_in_subsequence)
		{
			incresing_len++;
			last_element_in_subsequence = subsequence[i];
		}
		else
		{
			incresing_len = 0;
			last_element_in_subsequence = subsequence[i];
		}
		i++;
	}

	return incresing_len;
}