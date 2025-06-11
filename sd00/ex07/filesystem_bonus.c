#include "filesystem.h"

int		compute_total_size(const FSNode *node)
{
	int	total_size = 0;

	if (!node)
		return 0;

	for (int i = 0; i < node->childrenCount; i++)
	{
		if (node->children[i]->type == FILE_TYPE)
			total_size += node->children[i]->size;
		else if (node->children[i]->type == DIRECTORY_TYPE)
			total_size += compute_total_size(node->children[i]);
	}

	return total_size;
}

void	print_structure(const FSNode *node, int indent)
{
	if (!node)
		return;

	// Print indentation
	for (int i = 0; i < indent; i++)
		printf("  ");

	// Print node details
	printf("%s (%s, %d bytes)\n", 
		   node->name, 
		   node->type == FILE_TYPE ? "file" : "directory", 
		   node->type == FILE_TYPE ? node->size : compute_total_size(node));

	// Print children if it's a directory
	if (node->type == DIRECTORY_TYPE)
	{
		for (int i = 0; i < node->childrenCount; i++)
			print_structure(node->children[i], indent + 1);
	}
}

void	free_filesystem(FSNode *node)
{
	if (!node)
		return;

	for (int i = 0; i < node->childrenCount; i++)
		free_filesystem(node->children[i]);

	free(node->name);
	free(node->children);
	free(node);
}