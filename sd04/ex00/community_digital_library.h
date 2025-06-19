#ifndef COMMUNITY_DIGITAL_LIBRARY_H
#define COMMUNITY_DIGITAL_LIBRARY_H

#include <stdbool.h>

typedef struct Book Book;

typedef enum SearchMethod
{
	SEARCH_BY_TITLE,
	SEARCH_BY_AUTHOR,
} SearchMethod;

typedef struct Book
{
	int		id;
	char	*title;
	char	*author;
	int		year;
	Book	*next; // Pointer to the next book in the linked list, defult is NULL
} Book;

typedef struct Library
{
	Book	*books; // Pointer to the head of the linked list of books, default is NULL
	int		book_count;
} Library;

//-------------------INITIALIZATION-------------------//

Library	*create_library();

bool	load_catalog(const char *filename);

bool	is_line_valid(const char *line);

bool	add_book(Library *library, const char *title, const char *author, int year);

Book	*new_book(const char *title, const char *author, int year);

//-------------------SEARCHING-------------------//
// Doesn't allocate memory for the book, just create a list using the existing pointers

Book	*search(Library *library, const char *query, SearchMethod method);

Book	*search_by_title(Library *library, const char *title);

Book	*search_by_author(Library *library, const char *author);

//-------------------CLEANING-------------------//

void	free_library(Library *library);

void	free_book(Book *book);

#endif