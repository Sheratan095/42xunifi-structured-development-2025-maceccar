#ifndef CONTACT_MANAGER_BONUS_H
#define CONTACT_MANAGER_BONUS_H

#include <stdbool.h>
#include <stdio.h>

#define TARGET_FILE_EXTENSION ".csv"

typedef enum GroupType
{
	TEAM,
	VENDORS,
	FRIENDS,
	FAMILY,
	NONE,
} GroupType;

typedef enum SeatchType
{
	SEARCH_BY_NAME,
	SEARCH_BY_CITY,
	SEARCH_BY_GROUP,
} SearchType;

typedef struct Contact Contact;

typedef struct Contact
{
	int			id;
	char		*name;
	char		*phone;
	char		*email;
	char		*city;
	char		*address;
	GroupType	group;
	char		*date_of_birth;

	bool	removed;
	Contact	*next;
} Contact;

Contact		*load_contacts(const char *filename);

bool		check_file_extension(const char *filename);

void		save(const char *filename, Contact *contacts);

// used in the main loop, it will be false when the user types save-and-exit
bool		prompt(Contact *contacts);

void		print_warning(const char *error, const char *line, int line_number);

Contact		*add_contact(Contact *contacts, int id, const char *name, const char *phone, const char *email, const char *city, const char *address, GroupType group, const char *date_of_birth);

bool		remove_contact(Contact *contacts, int id);

bool		update_contact(Contact *contacts, int id, const char *new_name, const char *new_phone, const char *new_email, const char *new_city, const char *new_address, GroupType new_group, const char *new_date_of_birth);

void		show_all_contacts(Contact *contacts);

void		show_upcoming_birthdays(Contact *contacts); // in the next 30 days

Contact		*search(Contact *contacts, const char *query, SearchType search_type);

Contact		*search_by_name(Contact *contacts, const char *name);

Contact		*search_by_city(Contact *contacts, const char *city);

Contact		*search_by_group(Contact *contacts, GroupType group);

void		free_contacts(Contact *contacts);

void		free_contact(Contact *contact);

#endif