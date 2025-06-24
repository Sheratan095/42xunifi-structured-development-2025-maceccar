#ifndef MOVIE_WATCHLIST_H
#define MOVIE_WATCHLIST_H

#include <stdbool.h>
#include <stdio.h>

#define TARGET_FILE_EXTENSION ".csv"

typedef enum Type
{
	MOVIE,
	TV_SERIE,
	ANIME,
} Type;

typedef enum SearchType
{
	SEARCH_BY_TITLE,
	SEARCH_BY_DIRECTOR,
	SEARCH_BY_STATUS, // watched/unwatched
	SEARCH_BY_TYPE,
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

typedef struct View View;

typedef struct View
{
	int		id; // of media
	char	*date_watched; // format: YYYY-MM-DD
	int		rating;
	int		season; // 0 if not applicable (e.g., for movies)
	int		episode; // 0 if not applicable (e.g., for movies)

	View	*next;
} View;

typedef struct Media Media;

typedef struct Media
{
	int		id; // unique > 0
	char	*title;
	Genre	genre;
	bool	watched;
	View	*views;
	Type	type;

	bool	removed; // true if the movie is removed from the watchlist
	Media	*next;
} Media;

typedef struct Watchlist
{
	Media	*head;
	int		max_id;
} Watchlist;

Watchlist	*load_watchlist(const char *filename);

bool		check_file_extension(const char *filename);

void		free_watchlist(Watchlist *watchlist);

void		free_media(Media *media);

bool		save(const Watchlist *watchlist, const char *filename);

bool		prompt(Watchlist *watchlist);

Media		*add_media(Watchlist *watchlist, int id,  const char *title, Genre genre);

bool		remove_media(Watchlist *watchlist, int id);

bool		add_view(Watchlist *watchlist, int id, const char *date_watched, int rating, int season, int episode); // season and episode are 0 by default

bool		update_media(Watchlist *watchlist, int id, const char *new_title, Genre new_genre);

void		print_medias(const Watchlist *watchlist); //in ascending order by id

void		show_statistics(const Watchlist *watchlist);

Watchlist	*search(const Watchlist *watchlist, SearchType search_type, const char *query);

Watchlist	*search_by_title(const Watchlist *watchlist, const char *title);

Watchlist	*search_by_genre(const Watchlist *watchlist, Genre genre);

Watchlist	*search_by_status(const Watchlist *watchlist, bool watched);

Watchlist	*search_by_type(const Watchlist *watchlist, Type type);

#endif