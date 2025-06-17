#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Forward declaration of TaskList
struct TaskList;

typedef struct TaskProfile
{
	int	task_id;
	int	cpu_load;        // CPU load in percentage
	int	io_load;         // I/O load in percentage
	int	execution_time;  // Estimated execution time in milliseconds
} TaskProfile;

typedef struct PriorityMap
{
	int	task_id;
	int	priority;
} PriorityMap;

typedef struct LoadInfo
{
	int	cpu_load;
	int	io_load;
} LoadInfo;

typedef struct ScheduleResult
{
	int	*task_assignments; // Array of task IDs assigned to each core
	int	core_count;
} ScheduleResult;

typedef struct TaskList
{
	TaskProfile	*tasks;
	size_t	task_count;
} TaskList;

// Analyze task load and I/O behavior. Returns a new TaskProfile or NULL on failure.
struct TaskProfile	*profile_tasks(struct TaskList *tasks);

// Compute a priority map from task profiling. Returns a new PriorityMap or NULL on failure.
struct PriorityMap	*compute_priorities_mock(struct TaskProfile *profile);

// Return the number of available CPU cores.
int	get_available_core_count(void);

// Select the best task to assign next based on the profile. Returns a task ID or -1 on failure.
int	select_best_task_for_current_priorities(struct TaskProfile *profile, struct PriorityMap *priorities);

// Create a ScheduleResult structure for the specified number of cores. Returns NULL on failure.
struct ScheduleResult	*create_schedule_result(int core_count);

// Update the result schedule with a task assignment.
void	update_schedule_entry(struct ScheduleResult *result, int core_id, int task_id);

// Free functions for cleanup
void	free_task_profile(struct TaskProfile *profile);
void	free_priority_map(struct PriorityMap *priorities);
void	free_schedule_result(struct ScheduleResult *result);

struct ScheduleResult	*schedule_tasks(struct TaskList *tasks);

#endif