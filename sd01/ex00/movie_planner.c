#include "movie_planner.h"

struct Plan	*create_movie_night_plan(void)
{
	struct Preferences	*prefs = get_user_preferences();
	if (!prefs)
		return NULL;

	struct MovieList	*movie_list = find_movies(prefs);
	if (!movie_list)
	{
		free_preferences(prefs);
		return NULL;
	}

	struct Plan	*plan = build_plan(movie_list);
	if (!plan)
	{
		free_preferences(prefs);
		free_movie_list(movie_list);
		return NULL;
	}

	free_preferences(prefs);
	return plan;
}

void	free_preferences(struct Preferences *prefs)
{
	if (!prefs)
		return;
	
	while (prefs->next)
	{
		struct Preferences *next = prefs->next;
		free(prefs->username);
		free(prefs->preferred_genre);
		free(prefs);
		prefs = next;
	}
}

void	free_movie(struct Movie *movie)
{
	if (!movie)
		return;

	free(movie->title);
	free(movie->genres);
	free(movie);
}

void	free_movie_list(struct MovieList *list)
{
	if (!list)
		return;

	for (int i = 0; i < list->count; i++)
		free_movie(&list->movies[i]);

	free(list->movies);
	free(list);
}

void	free_plan(struct Plan *plan)
{
	if (!plan)
		return;

	free_movie_list(&plan->movie_list);
	free(plan);
}