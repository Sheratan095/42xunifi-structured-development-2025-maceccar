#include "grade_map.h"
#include <stdio.h>

void	map_scores(const int *scores, int size, GradeMapper mapper, const char **mapped_grades)
{
	for (int i = 0; i < size; i++)
		mapped_grades[i] = mapper(scores[i]); // Initialize the mapped grades array
}

const char	*plusminus_mapper(int score)
{
	if (score < 0 || score > 100)
		return "Invalid score";

	if (score <= 59)
		return "F";
	else if (score <= 62)
		return "D-";
	else if (score <= 66)
		return "D";
	else if (score <= 69)
		return "D+";
	else if (score <= 72)
		return "C-";
	else if (score <= 76)
		return "C";
	else if (score <= 79)
		return "C+";
	else if (score <= 82)
		return "B-";
	else if (score <= 86)
		return "B";
	else if (score <= 89)
		return "B+";
	else if (score <= 92)
		return "A-";
	else if (score <= 96)
		return "A";
	else
		return "A+";
}

const char *passfail_mapper(int score)
{
	if (score < 0 || score > 100)
		return "Invalid score";

	if (score < 60)
		return "F";

	return "P";
}

const char *standard_mapper(int score)
{
	if (score < 0 || score > 100)
		return "Invalid score";

	if (score < 60)
		return "F";
	if (score < 70)
		return "D";
	if (score < 80)
		return "C";
	if (score < 90)
		return "B";
	if (score <= 100)
		return "A";

	return "Invalid score";
}

int main()
{
	// Create a test array with scores covering the full range
	int scores[] = {0, 45, 59, 60, 65, 72, 78, 82, 87, 90, 95, 100, 105};
	int size = sizeof(scores) / sizeof(scores[0]);
	const char *mapped_grades[size];
	
	printf("=== Testing Plus/Minus Grading ===\n");
	map_scores(scores, size, plusminus_mapper, mapped_grades);
	for (int i = 0; i < size; i++)
		printf("Score %3d: %s\n", scores[i], mapped_grades[i]);
	
	printf("\n=== Testing Pass/Fail Grading ===\n");
	map_scores(scores, size, passfail_mapper, mapped_grades);
	for (int i = 0; i < size; i++)
		printf("Score %3d: %s\n", scores[i], mapped_grades[i]);
	
	printf("\n=== Testing Standard Grading ===\n");
	map_scores(scores, size, standard_mapper, mapped_grades);
	for (int i = 0; i < size; i++)
		printf("Score %3d: %s\n", scores[i], mapped_grades[i]);

	return 0;
}