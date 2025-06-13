#include "music_organizer.h"

struct MusicLibrary	*organize_music_library(const char *directory_path)
{
	MusicLibrary	*new_lib;
	int	i = 0;

	if (!directory_path)
		return NULL;

	const char	**file_names = scan_directory(directory_path);
	if (!file_names)
		return NULL;

	new_lib = create_music_library();
	if (!new_lib)
	{
		free_matrix((char **)file_names);
		return NULL;
	}

	while (file_names[i])
	{
		MusicFile	*processed_file = process_music_file(directory_path, file_names[i]);
		if (processed_file)
			update_music_library(new_lib, processed_file);
		i++;
	}

	free_matrix((char **)file_names);
	return new_lib;
}

void	free_matrix(char **mtx)
{
	int	i = 0;

	if (!mtx)
		return ;

	while (mtx[i])
		free(mtx[i++]);
	
	free(mtx);
}