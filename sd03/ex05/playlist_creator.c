
#include "playlist_creator.h"

struct Playlist	*create_playlist(void)
{
	MoodSettings	*mood = analyze_user_mood();
	if (!mood)
		return NULL; // Failed to analyze mood

	FilterSettings	*filter = default_filters();
	while (get_mood_variations(mood) > 0)
	{
		free_filter_settings(filter);
		filter = refine_filters(filter);
		if (!filter)
		{
			free_mood_settings(mood);
			return NULL; // Failed to refine filters
		}
	}

	SongData	*requested_song = NULL;
	if (filters_require_popular_song(filter))
		requested_song = fetch_popular_song();
	else
		requested_song = fetch_niche_song();

	if (!requested_song)
	{
		free_mood_settings(mood);
		free_filter_settings(filter);
		return NULL; // Failed to fetch song
	}

	Playlist	*playlist = combine_with_mood_playlist(requested_song, mood);

	free_song_data(requested_song);
	free_mood_settings(mood);
	free_filter_settings(filter);
	
	return playlist; // Return the created playlist
}

