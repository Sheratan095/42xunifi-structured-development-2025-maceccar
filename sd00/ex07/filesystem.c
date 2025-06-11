#include "filesystem.h"

FSNode	*create_file(const char *name, int size)
{
	FSNode	*file = malloc(sizeof(FSNode));
	if (!file)
		return NULL;

	file->name = strdup(name);
	if (!file->name)
	{
		// free(file); not allowed function
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
		// free(folder); not allowed function
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
	const FSNode	*parent = node->parent;
	for (int i = 0; i < parent->childrenCount; i++)
	{
		if (parent->children[i] != node)
			return parent->children[i];
	}

	return NULL;
}

// int main()
// {
// 	printf("=== Testing Filesystem Implementation ===\n\n");
	
// 	// Test creation functions
// 	printf("Creating filesystem structure...\n");
// 	FSNode *root = create_folder("root");
// 	FSNode *documents = create_folder("Documents");
// 	FSNode *pictures = create_folder("Pictures");
// 	FSNode *resume = create_file("resume.pdf", 1024);
// 	FSNode *notes = create_file("notes.txt", 256);
// 	FSNode *vacation = create_file("vacation.jpg", 2048);
// 	FSNode *selfie = create_file("selfie.jpg", 1536);
	
// 	printf("Adding children to folders...\n");
// 	add_child(root, documents);
// 	add_child(root, pictures);
// 	add_child(documents, resume);
// 	add_child(documents, notes);
// 	add_child(pictures, vacation);
// 	add_child(pictures, selfie);
	
// 	printf("\nTesting get_children:\n");
// 	FSNode *root_child = get_children(root);
// 	if (root_child)
// 		printf("First child of root: %s\n", root_child->name);
// 	else
// 		printf("Error: No children found for root\n");
	
// 	FSNode *doc_child = get_children(documents);
// 	if (doc_child)
// 		printf("First child of Documents: %s\n", doc_child->name);
// 	else
// 		printf("Error: No children found for Documents\n");
//	
// 	printf("\nTesting get_sibling:\n");
// 	FSNode *doc_sibling = get_sibling(documents);
// 	if (doc_sibling)
// 		printf("Sibling of Documents: %s\n", doc_sibling->name);
// 	else
// 		printf("Error: No siblings found for Documents\n");
//
// 	FSNode *resume_sibling = get_sibling(resume);
// 	if (resume_sibling)
// 		printf("Sibling of resume.pdf: %s\n", resume_sibling->name);
// 	else
// 		printf("Error: No siblings found for resume.pdf\n");
// 	// Test bonus functions
// 	printf("\n=== Testing Bonus Functions ===\n\n");
	
// 	// Test compute_total_size
// 	printf("Testing compute_total_size:\n");
// 	int docs_size = compute_total_size(documents);
// 	printf("Total size of Documents: %d bytes\n", docs_size);
	
// 	int pics_size = compute_total_size(pictures);
// 	printf("Total size of Pictures: %d bytes\n", pics_size);
	
// 	int root_size = compute_total_size(root);
// 	printf("Total size of root: %d bytes\n", root_size);
	
// 	// Test print_structure
// 	printf("\nTesting print_structure:\n");
// 	print_structure(root, 0);
	
// 	// Clean up
// 	printf("\nCleaning up filesystem...\n");
// 	free_filesystem(root);
// 	printf("Filesystem freed successfully\n");
	
// 	return 0;
// }