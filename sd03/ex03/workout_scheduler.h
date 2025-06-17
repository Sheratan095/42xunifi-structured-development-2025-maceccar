#ifndef WORKOUT_SCHEDULER_H
#define WORKOUT_SCHEDULER_H

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum FitnessLevel
{
	FITNESS_LEVEL_BEGINNER,
	FITNESS_LEVEL_INTERMEDIATE,
	FITNESS_LEVEL_ADVANCED,
	FITNESS_LEVEL_PROFESSIONAL,
	FITNESS_LEVEL_ELITE
} FitnessLevel;

// Forward declarations
struct WorkoutPlan;

typedef struct UserData
{
	char			*username;
	int				age;
	FitnessLevel	fitness_level;
	struct WorkoutPlan	*workout_plan;// current plan
} UserData;

typedef struct Exercise
{
	char			*name;
	int				sets;
	int				repetitions;
	char 			description;
} Exercise;

typedef struct DailyPlan
{
	Exercise	exercises[32];
	int			num_exercises;
	char		**tips;
} DailyPlan;

typedef struct WorkoutPlan
{
	UserData		*user_data;
	int				current_day;
	int				total_days;
	DailyPlan		daily_plans[30];
} WorkoutPlan;

// Returns a new UserData (mocked). Returns NULL on failure.
struct UserData	*get_user_data(char *username);

// Build a base WorkoutPlan from raw user data. Returns NULL on failure.
struct WorkoutPlan	*build_base_plan(struct UserData *data);

// Optionally refine an existing plan. Returns the same pointer (or a new one) or NULL on failure.
struct WorkoutPlan	*refine_plan(struct WorkoutPlan *plan, struct UserData *data);

// Determine how many days the workout schedule should span. Returns positive int, or <=0 on failure.
int		determine_duration(struct WorkoutPlan *plan);

// Assign daily exercises for the next day into the plan.
void	assign_daily_exercises(struct WorkoutPlan *plan, int day);

// Assign daily tips for the next day into the plan.
void	assign_daily_tips(struct WorkoutPlan *plan, int day);

// Free functions for cleanup.
void	free_user_data(struct UserData *data);
void	free_workout_plan(struct WorkoutPlan *plan);

struct WorkoutPlan	*create_workout_schedule(char *username);

// void	free_exercise(Exercise *exercise);
// void	free_daily_plan(DailyPlan *daily_plan);

void	assign_new_workout_plan(struct WorkoutPlan *plan, char *username);

#endif