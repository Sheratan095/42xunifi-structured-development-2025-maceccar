#ifndef MOVIE_PLANNER_H
#define MOVIE_PLANNER_H

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum Genre
{
	GENRE_ACTION,
	GENRE_COMEDY,
	GENRE_DRAMA,
	GENRE_HORROR,
	GENRE_ROMANCE,
	GENRE_SCI_FI,
	GENRE_THRILLER,
	GENRE_ANIMATION,
	GENRE_DOCUMENTARY,
	GENRE_FANTASY
} Genre;

typedef struct Preferences
{
	char		*username;
	Genre		*preferred_genre;
	Preferences	*next;
} Preferences;

typedef struct Movie
{
	char	*title;
	int		duration;
	Genre	*genres;
} Movie;

typedef struct MovieList
{
	Movie	*movies;
	int		count;
} MovieList;

typedef struct Plan
{
	MovieList movie_list;
} Plan;


// Returns user preferences. Returns NULL on failure.
struct Preferences	*get_user_preferences(void);

// Returns a list of movies matching the given preferences. Returns NULL on failure.
struct MovieList	*find_movies(struct Preferences *prefs);

// Returns a movie night plan from the given list. Returns NULL on failure.
struct Plan	*build_plan(struct MovieList *list);

struct Plan	*create_movie_night_plan(void);

void	free_preferences(struct Preferences *prefs);
void	free_movie(struct Movie *movie);
void	free_movie_list(struct MovieList *list);

#endif