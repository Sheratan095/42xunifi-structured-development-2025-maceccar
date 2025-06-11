#include "filesystem.h"

FSNode	*create_file(const char *name, int size)
{
	FSNode	*file = malloc(sizeof(FSNode));
	if (!file)
		return NULL;

	file->name = strdup(name);
	if (!file->name)
	{
		free(file);
		return NULL;
	}

	file->size = size;
	file->type = FILE_TYPE;
	file->children = NULL;
	file->parent = NULL;
	file->childrenCount = 0;

	return file;
}

FSNode	*create_folder(const char *name)
{
	FSNode	*folder = malloc(sizeof(FSNode));
	if (!folder)
		return NULL;

	folder->name = strdup(name);
	if (!folder->name)
	{
		free(folder);
		return NULL;
	}

	folder->size = 0;
	folder->type = DIRECTORY_TYPE;
	folder->children = NULL;
	folder->parent = NULL;
	folder->childrenCount = 0;

	return folder;
}

void	add_child(FSNode *parent, FSNode *child)
{
	// check on child->parent to ensure it is not already in another directory
	if (!parent || !child || parent->type != DIRECTORY_TYPE || child->parent)
		return;

	child->parent = parent;

	// Resize the children array to accommodate the new child
	FSNode	**new_children = realloc(parent->children, sizeof(FSNode *) * (parent->childrenCount + 1));
	if (!new_children)
		return ;

	parent->children = new_children;
	parent->children[parent->childrenCount] = child;
	parent->childrenCount++;
}

FSNode	*get_children(const FSNode *parent)
{
	if (!parent || parent->type != DIRECTORY_TYPE)
		return NULL;

	return parent->children[0];
}

FSNode	*get_sibling(const FSNode *node)
{
	if (!node || !node->parent)
		return NULL;

	// Find the first sibling of the node that is not the node itself
	FSNode	*parent = node->parent;
	for (int i = 0; i < parent->childrenCount; i++)
	{
		if (parent->children[i] != node)
			return parent->children[i];
	}

	return NULL;
}