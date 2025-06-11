#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesystem.h"

void print_node_info(FSNode *node, int indent) {
    if (!node)
        return;
    
    // Print indentation
    for (int i = 0; i < indent; i++)
        printf("  ");
    
    // Print node details
    printf("%s (%s, %d bytes)\n", 
           node->name, 
           node->type == FILE_TYPE ? "file" : "directory", 
           node->size);
    
    // Print children if it's a directory
    if (node->type == DIRECTORY_TYPE) {
        for (int i = 0; i < node->childrenCount; i++) {
            print_node_info(node->children[i], indent + 1);
        }
    }
}

int main() {
    printf("Filesystem Test Program\n");
    printf("======================\n\n");
    
    // Test 1: Create a file
    printf("Test 1: Creating a file...\n");
    FSNode *file1 = create_file("document.txt", 1024);
    if (file1 && strcmp(file1->name, "document.txt") == 0 && 
        file1->size == 1024 && file1->type == FILE_TYPE) {
        printf("PASS: File created successfully\n\n");
    } else {
        printf("FAIL: File creation failed\n\n");
        return 1;
    }
    
    // Test 2: Create a folder
    printf("Test 2: Creating a folder...\n");
    FSNode *folder1 = create_folder("Documents");
    if (folder1 && strcmp(folder1->name, "Documents") == 0 && 
        folder1->type == DIRECTORY_TYPE) {
        printf("PASS: Folder created successfully\n\n");
    } else {
        printf("FAIL: Folder creation failed\n\n");
        return 1;
    }
    
    // Test 3: Add child to folder
    printf("Test 3: Adding child to folder...\n");
    add_child(folder1, file1);
    if (folder1->childrenCount == 1 && file1->parent == folder1) {
        printf("PASS: Child added successfully\n\n");
    } else {
        printf("FAIL: Adding child failed\n\n");
        return 1;
    }
    
    // Test 4: Create more files and folders to test structure
    printf("Test 4: Creating more complex structure...\n");
    FSNode *file2 = create_file("image.jpg", 2048);
    FSNode *file3 = create_file("notes.txt", 512);
    FSNode *subfolder = create_folder("Images");
    FSNode *file4 = create_file("profile.png", 4096);
    
    add_child(folder1, file2);
    add_child(folder1, subfolder);
    add_child(subfolder, file4);
    add_child(folder1, file3);
    
    // Print the structure to check it visually
    printf("Filesystem structure:\n");
    print_node_info(folder1, 0);
    printf("\n");
    
    // Test 5: Test get_children
    printf("Test 5: Testing get_children...\n");
    FSNode *first_child = get_children(folder1);
    if (first_child && first_child == file1) {
        printf("PASS: get_children returns first child correctly\n\n");
    } else {
        printf("FAIL: get_children failed\n\n");
        return 1;
    }
    
    // Test 6: Test get_sibling
    printf("Test 6: Testing get_sibling...\n");
    FSNode *sibling = get_sibling(file1);
    if (sibling && (sibling == file2 || sibling == subfolder || sibling == file3)) {
        printf("PASS: get_sibling returns a sibling correctly\n\n");
    } else {
        printf("FAIL: get_sibling failed\n\n");
        return 1;
    }
    
    // Test 7: Test error handling
    printf("Test 7: Testing error handling...\n");
    
    // Try to add a directory to a file (should fail)
    FSNode *invalid_folder = create_folder("Invalid");
    add_child(file1, invalid_folder);
    
    if (file1->childrenCount == 0) {
        printf("PASS: Cannot add child to a file\n");
    } else {
        printf("FAIL: Should not be able to add child to a file\n");
        return 1;
    }
    
    // Try to get children from a file (should return NULL)
    if (get_children(file1) == NULL) {
        printf("PASS: get_children returns NULL for files\n");
    } else {
        printf("FAIL: get_children should return NULL for files\n");
        return 1;
    }
    
    printf("\nAll tests completed successfully!\n");
    
    // Clean up (in a real program, we would free all the memory here)
    // TODO: Implement a cleanup function to free all allocated memory
    
    return 0;
}
