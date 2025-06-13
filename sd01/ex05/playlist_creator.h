#ifndef PLAYLIST_CREATOR_H
#define PLAYLIST_CREATOR_H

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum MoodType
{
	MOOD_TYPE_HAPPY,
	MOOD_TYPE_SAD,
	MOOD_TYPE_ENERGETIC,
	MOOD_TYPE_RELAXED,
	MOOD_TYPE_MOTIVATIONAL
} MoodType;

typedef enum Genre
{
	GENRE_POP,
	GENRE_ROCK,
	GENRE_JAZZ,
	GENRE_CLASSICAL,
	GENRE_HIPHOP,
	GENRE_ELECTRONIC
} Genre;

typedef struct MoodSettings
{
	MoodType	mood;
	int			intensity;
	int			duration;
} MoodSettings;

typedef struct FilterSettings
{
	int			min_duration;
	int			max_duration;
	int			energy_level;

	Genre		*genre;
	int			num_genres;
} FilterSettings;

typedef struct SongData
{
	char		*title;
	char		*artist;
	int			duration; // Duration in seconds
	Genre		genre;
} SongData;

typedef struct Playlist
{
	SongData	*songs;
	int			num_songs;
} Playlist;


// Analyze user mood. Returns a new MoodSettings or NULL on failure.
struct MoodSettings *analyze_user_mood(void);

// Return default filter settings. Returns a new FilterSettings or NULL on failure.
struct FilterSettings *default_filters(void);

// Return the number of mood variations for refinement.
int get_mood_variations(struct MoodSettings *mood);

// Refine the current filter settings. Returns the same or a new FilterSettings, or NULL on failure.
struct FilterSettings *refine_filters(struct FilterSettings *current);

// Check if filters require a popular or niche song. Returns nonzero if popular.
int filters_require_popular_song(struct FilterSettings *filters);

// Fetch a popular song. Returns a new SongData or NULL on failure.
struct SongData *fetch_popular_song(void);

// Fetch a niche song. Returns a new SongData or NULL on failure.
struct SongData *fetch_niche_song(void);

// Combine a song into a playlist given mood settings. Returns a new Playlist or NULL on failure.
struct Playlist *combine_with_mood_playlist(struct SongData *song, struct MoodSettings *mood);

// Free functions for cleanup
void	free_mood_settings(struct MoodSettings *mood);
void	free_filter_settings(struct FilterSettings *filters);
void	free_song_data(struct SongData *song);
void	free_playlist(struct Playlist *playlist);

struct Playlist	*create_playlist(void);

#endif