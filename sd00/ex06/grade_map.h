#ifndef GRADE_MAP_H
#define GRADE_MAP_H

// pointer to a function that takes an integer score and returns a string representing the grade
typedef const char *(*GradeMapper)(int score);

void	map_scores(const int *scores, int size, GradeMapper mapper, const char **mapped_grades);

#endif