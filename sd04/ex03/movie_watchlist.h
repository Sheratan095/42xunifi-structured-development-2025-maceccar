#ifndef MOVIE_WATCHLIST_H
#define MOVIE_WATCHLIST_H

#include <stdbool.h>
#include <stdio.h>

#define TARGET_FILE_EXTENSION ".csv"

typedef enum SearchType
{
	SEARCH_BY_TITLE,
	SEARCH_BY_DIRECTOR,
	SEARCH_BY_STATUS, // watched/unwatched
} SearchType;

typedef enum Genre {
	ACTION,
	COMEDY,
	DRAMA,
	HORROR,
	SCIFI,
	ROMANCE,
	THRILLER,
	DOCUMENTARY
} Genre;

typedef struct Movie Movie;

typedef struct Movie
{
	int		id; // unique > 0
	char	*title;
	Genre	genre;
	bool	watched;
	int		rating; // 0-10 scale
	char	*date_watched; // format: YYYY-MM-DD

	bool	removed; // true if the movie is removed from the watchlist
	Movie	*next;
} Movie;

typedef struct Watchlist
{
	Movie	*head;
	int		max_id;
} Watchlist;

Watchlist	*load_movies(const char *filename);

bool		check_file_extension(const char *filename);

void		free_watchlist(Watchlist *watchlist);

void		free_movie(Movie *movie);

bool		save(const Watchlist *watchlist, const char *filename);

bool		prompt(Watchlist *watchlist);

Movie		*add_movie(Watchlist *watchlist, int id,  const char *title, Genre genre, int rating, const char *date_watched);

bool		remove_movie(Watchlist *watchlist, int id);

bool		mark_as_watched(Watchlist *watchlist, int id, const char *date_watched, int rating);

bool		update_movie(Watchlist *watchlist, int id, const char *new_title, Genre new_genre);

void		print_movies(const Watchlist *watchlist); //in ascending order by id

void		show_statistics(const Watchlist *watchlist);

Watchlist	*search(const Watchlist *watchlist, SearchType search_type, const char *query);

Watchlist	*search_by_title(const Watchlist *watchlist, const char *title);

Watchlist	*search_by_genre(const Watchlist *watchlist, Genre genre);

Watchlist	*search_by_status(const Watchlist *watchlist, bool watched);

#endif