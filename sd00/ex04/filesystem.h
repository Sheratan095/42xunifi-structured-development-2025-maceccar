#ifdef FILESYSTEM_H
#define FILESYSTEM_H

typedef struct FSNode
{
	char *name;
	int size;	   // Size in bytes
	NodeType type; // Type of the node (file or directory)
	struct FSNode **children;
	struct FSNode *parent;
	int childCount;
} FSNode;

#endif