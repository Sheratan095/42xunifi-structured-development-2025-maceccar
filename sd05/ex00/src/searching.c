#include "contact_manager.h"

static char *ft_strtolower(char *str);

Contact *search(Contact *contacts, const char *query, SearchType search_type)
{
	if (!contacts || !query)
		return NULL;
	
	// Trim any newline character that might be present
	char *trimmed_query = ft_strtrim((char *)query, "\n\r", false);
	if (!trimmed_query || *trimmed_query == '\0')
	{
		free(trimmed_query);
		return NULL;
	}
	
	Contact *results = NULL;
	Contact *current = contacts;
	int matches_found = 0;
	
	while (current)
	{
		if (!current->removed)
		{
			t_bool match = false;
			
			if (search_type == SEARCH_BY_NAME)
			{
				// Check for exact match or substring within name (case insensitive)
				char *name_copy = ft_strdup(current->name);
				if (!name_copy)
				{
					free(trimmed_query);
					return NULL;
				}
				
				char *lowercase_name = ft_strtolower(name_copy);
				free(name_copy); // Free the intermediate copy
				
				char *query_copy = ft_strdup(trimmed_query);
				if (!query_copy)
				{
					free(lowercase_name);
					free(trimmed_query);
					return NULL;
				}
				
				char *lowercase_query = ft_strtolower(query_copy);
				free(query_copy); // Free the intermediate copy
				
				if (lowercase_name && lowercase_query && 
					ft_strnstr(lowercase_name, lowercase_query, ft_strlen(lowercase_name)) != NULL)
				{
					match = true;
				}
				
				free(lowercase_name);
				free(lowercase_query);
			}
			else if (search_type == SEARCH_BY_CITY)
			{
				// Similarly fix memory leaks for city search
				char *city_copy = ft_strdup(current->city);
				if (!city_copy)
				{
					free(trimmed_query);
					return NULL;
				}
				
				char *lowercase_city = ft_strtolower(city_copy);
				free(city_copy); // Free the intermediate copy
				
				char *query_copy = ft_strdup(trimmed_query);
				if (!query_copy)
				{
					free(lowercase_city);
					free(trimmed_query);
					return NULL;
				}
				
				char *lowercase_query = ft_strtolower(query_copy);
				free(query_copy); // Free the intermediate copy
				
				if (lowercase_city && lowercase_query && 
					ft_strnstr(lowercase_city, lowercase_query, ft_strlen(lowercase_city)) != NULL)
				{
					match = true;
				}
				
				free(lowercase_city);
				free(lowercase_query);
			}
			
			if (match)
			{
				// Print matching contact
				print_contact(current);
				matches_found++;
			}
		}
		current = current->next;
	}
	
	free(trimmed_query);
	return results; // Currently we're just printing results, not building a new list
}

Contact *search_by_name(Contact *contacts, const char *name)
{
	return search(contacts, name, SEARCH_BY_NAME);
}

Contact *search_by_city(Contact *contacts, const char *city)
{
	return search(contacts, city, SEARCH_BY_CITY);
}

static char *ft_strtolower(char *str)
{
	if (!str)
		return NULL;
	
	size_t len = ft_strlen(str);
	char *result = malloc(len + 1);
	if (!result)
		return NULL;
	
	// Copy and convert to lowercase at the same time
	for (size_t i = 0; i <= len; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z')
			result[i] = str[i] + ('a' - 'A');
		else
			result[i] = str[i];
	}
	
	return result;
}
