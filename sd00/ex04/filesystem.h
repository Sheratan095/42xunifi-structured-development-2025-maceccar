#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef enum Type
{
	FILE_TYPE,
	DIRECTORY_TYPE
} Type;

typedef struct FSNode
{
	char			*name;
	int				size; // in bytes
	Type			type;
	struct FSNode	**children;
	struct FSNode	*parent;
	int				childrenCount;
} FSNode;

FSNode	*create_file(const char *name, int size);

FSNode	*create_folder(const char *name);

void	add_child(FSNode *parent, FSNode *child);

FSNode	*get_children(const FSNode *parent);

FSNode	*get_sibling(const FSNode *node);

#endif