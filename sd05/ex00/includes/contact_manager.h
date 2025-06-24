#ifndef CONTACT_MANAGER_H
#define CONTACT_MANAGER_H

#include <stdio.h>
#include "corekit.h"

#define TARGET_FILE_EXTENSION ".csv"

#define EXIT_COMMAND "save-and-exit"

typedef enum SeatchType
{
	SEARCH_BY_NAME,
	SEARCH_BY_CITY,
} SearchType;

typedef struct Contact Contact;

typedef struct Contact
{
	int		id;
	char	*name;
	char	*phone;
	char	*email;
	char	*city;
	char	*address;


	int		max_id;
	t_bool	removed;
	Contact	*next;
} Contact;

Contact		*load_contacts(const char *filename);

t_bool		check_file_extension(const char *filename);

t_bool		save(const char *filename, Contact *contacts);

void		prompt(Contact *contacts);

Contact		*add_contact(Contact *contacts, int id, const char *name, const char *phone, const char *email, const char *city, const char *address);

t_bool		remove_contact(Contact *contacts, int id);

t_bool		update_contact(Contact *contacts, int id, const char *new_name, const char *new_phone, const char *new_email, const char *new_city, const char *new_address);

void		show_all_contacts(Contact *contacts);

Contact		*search(Contact *contacts, const char *query, SearchType search_type);

Contact		*search_by_name(Contact *contacts, const char *name);

Contact		*search_by_city(Contact *contacts, const char *city);

void		free_contacts(Contact *contacts);

void		free_contact(Contact *contact);

#endif