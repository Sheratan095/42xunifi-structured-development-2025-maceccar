#include "task_scheduler.h"

struct ScheduleResult *schedule_tasks(struct TaskList *tasks)
{
	struct TaskProfile	*profiles = profile_tasks(tasks);
	if (!profiles)
		return NULL;
	
	struct PriorityMap	*priorities = compute_priorities_mock(profiles);
	if (!priorities)
	{
		free_task_profile(profiles);
		return NULL;
	}
	
	int	core_count = get_available_core_count();
	if (core_count <= 0)
	{
		free_task_profile(profiles);
		free_priority_map(priorities);
		return NULL;
	}
	
	struct ScheduleResult	*result = create_schedule_result(core_count);
	if (!result)
	{
		free_task_profile(profiles);
		free_priority_map(priorities);
		return NULL;
	}
	
	// Step 5: Select the best task for each core
	for (int i = 0; i < core_count; i++)
	{
		int task_id = select_best_task_for_current_priorities(profiles, priorities);
		if (task_id == -1)
			break;

		// Assign the selected task to the current core
		update_schedule_entry(result, i, task_id);
	}
	
	free_task_profile(profiles);
	free_priority_map(priorities);
	
	return result;
}
