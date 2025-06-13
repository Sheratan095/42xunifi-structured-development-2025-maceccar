
#include "workout_scheduler.h"

struct WorkoutPlan	*create_workout_schedule(char *username)
{
	struct UserData	*data = get_user_data(username);
	if (!data)
		return NULL;

	WorkoutPlan	*plan;

	// If a plan already exists, refine it
	if (data->workout_plan) 
		plan = refine_plan(data->workout_plan, data);
	else
		plan = build_base_plan(data);
	
	free(data);

	if (!plan)
		return NULL;

	int duration = determine_duration(plan);
	if (duration <= 0)
	{
		free(plan);
		return NULL;
	}

	for (size_t i = 0; i < duration; i++)
	{
		assign_daily_exercises(plan, i);
		assign_daily_tips(plan, i);
	}

	return plan;
}

void	free_exercise(Exercise *exercise)
{
	if (!exercise)
		return;

	free(exercise->name);
	free(exercise);
}

void	free_daily_plan(DailyPlan *daily_plan)
{
	if (!daily_plan)
		return;

	for (int i = 0; i < daily_plan->num_exercises; i++)
		free_exercise(&daily_plan->exercises[i]);

	for (int j = 0; daily_plan->tips && daily_plan->tips[j]; j++)
		free(daily_plan->tips[j]);

	free(daily_plan->tips);
	free(daily_plan);
}