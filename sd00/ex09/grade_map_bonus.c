#include "grade_map.h"
#include <stdlib.h>
#include <string.h>

GradeNode	*compute_distribution(const char **mapped_grades, int size)
{
	if (mapped_grades == NULL || size <= 0)
		return NULL;

	GradeNode	*head = NULL;
	
	// Process each grade in the array
	for (int i = 0; i < size; i++)
	{
		const char	*current_grade = mapped_grades[i];
		if (!current_grade)
			continue;  // Skip NULL entries
		
		// Check if this grade already exists in our list
		GradeNode	*current = head;
		bool		found = false;
		while (current)
		{
			if (strcmp(current->grade, current_grade) == 0)
			{
				// Found the grade, increment its count
				current->count++;
				found = true;
				break;
			}
			current = current->next;
		}

		// If grade wasn't found, create a new node
		if (!found)
		{
			GradeNode *new_node = (GradeNode *)malloc(sizeof(GradeNode));
			if (!new_node)
				continue;

			int	grade_len = ft_strlen(current_grade);
			char *grade_copy = (char *)malloc(grade_len + 1);
			if (!grade_copy) //mem check
			{
				free(new_node);
				continue ;
			}

			// Copy the grade string
			strncpy(grade_copy, current_grade, grade_len);
			grade_copy[grade_len] = '\0';  // Ensure null termination

			new_node->grade = grade_copy;
			new_node->count = 1;
			new_node->next = head;  // Insert at the beginning
			head = new_node;
		}
	}

	return head;
}

void	print_distribution(GradeNode *head)
{
	if (head == NULL)
	{
		printf("No grades to display.\n");
		return;
	}

	printf("Grade Distribution:\n");
	printf("--------------------\n");

	GradeNode	*current = head;
	while (current)
	{
		printf("%s: %d\n", current->grade, current->count);
		current = current->next;
	}

	printf("--------------------\n");
}

// Helper function to free the grade distribution linked list
void free_distribution(GradeNode *head)
{
	GradeNode	*current = head;

	while (current)
	{
		GradeNode	*next = current->next;
		free((void *)current->grade);
		free(current);
		current = next;
	}
}

int	ft_strlen(const char *str)
{
	int len = 0;
	while (str[len] != '\0')
		len++;
	return len;
}







// int main(void)
// {
// 	printf("=== Testing Grade Distribution ===\n\n");

// 	// Test 1: Normal distribution with multiple grades
// 	// This test should map scores to grades using plusminus_mapper
// 	// Expected grades should be: F, F, F, D-, D, C-, C, B-, B, A-, A, A+, Invalid
// 	// Expected distribution: F:3, D-:1, D:1, C-:1, C:1, B-:1, B:1, A-:1, A:1, A+:1, Invalid:2
// 	int scores[] = {0, 45, 59, 60, 65, 72, 78, 82, 87, 90, 95, 100, 105, -1};
// 	int size = sizeof(scores) / sizeof(scores[0]);
// 	const char *grades1[size];

// 	map_scores(scores, size, plusminus_mapper, grades1);

// 	printf("Test 1: Normal distribution\n");
// 	GradeNode *dist1 = compute_distribution(grades1, size);
// 	print_distribution(dist1);
// 	free_distribution(dist1);
	
// 	// Test 2: All same grade
// 	const char *grades2[] = {"B", "B", "B", "B", "B"};
// 	int size2 = 5;
	
// 	printf("\nTest 2: All same grade\n");
// 	GradeNode *dist2 = compute_distribution(grades2, size2);
// 	print_distribution(dist2);
// 	free_distribution(dist2);
	
// 	// Test 3: Empty array
// 	const char *grades3[] = {};
// 	int size3 = 0;
	
// 	printf("\nTest 3: Empty array\n");
// 	GradeNode *dist3 = compute_distribution(grades3, size3);
// 	print_distribution(dist3);
// 	free_distribution(dist3);
	
// 	// Test 4: Array with NULL values
// 	const char *grades4[] = {"A", NULL, "C", NULL, "B"};
// 	int size4 = 5;
	
// 	printf("\nTest 4: Array with NULL values\n");
// 	GradeNode *dist4 = compute_distribution(grades4, size4);
// 	print_distribution(dist4);
// 	free_distribution(dist4);
	
// 	// Test 5: Using the plusminus grade scale
// 	const char *grades5[] = {"A+", "A", "A-", "B+", "B", "B-", "C+", "C", "A", "A-"};
// 	int size5 = 10;
	
// 	printf("\nTest 5: Plus/minus grade scale\n");
// 	GradeNode *dist5 = compute_distribution(grades5, size5);
// 	print_distribution(dist5);
// 	free_distribution(dist5);
	
// 	return 0;
// }