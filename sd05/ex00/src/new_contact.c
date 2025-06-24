#include "contact_manager.h"

static t_bool	is_valid_id(Contact *contacts, int	id);
t_bool			is_valid_phone(const char *phone);
t_bool			is_valid_email(const char *email);

Contact		*add_contact(Contact *contacts, int id, const char *name, const char *phone, const char *email, const char *city, const char *address)
{
	// Validate all fields before adding
	if (!is_valid_id(contacts, id) || !name || !phone || !email || !city || !address)
		return NULL;
		
	if (ft_strlen(name) == 0 || ft_strlen(city) == 0)
		return NULL;
		
	if (!is_valid_phone(phone) || !is_valid_email(email))
		return NULL;

	if (contacts == NULL)
	{
		contacts = malloc(sizeof(Contact));
		if (!contacts)
			return NULL;
		
		// Initialize the first contact
		contacts->id = id;
		contacts->name = ft_strdup((char *)name);
		contacts->phone = ft_strdup((char *)phone);
		contacts->email = ft_strdup((char *)email);
		contacts->city = ft_strdup((char *)city);
		contacts->address = ft_strdup((char *)address);
		contacts->removed = false;
		contacts->next = NULL;
		
		return contacts;
	}
	else
	{
		// Create a new contact and add it to the linked list
		Contact *head = contacts;
		Contact *new_node = malloc(sizeof(Contact));
		if (!new_node)
			return head;
		
		new_node->id = id;
		new_node->name = ft_strdup((char *)name);
		new_node->phone = ft_strdup((char *)phone);
		new_node->email = ft_strdup((char *)email);
		new_node->city = ft_strdup((char *)city);
		new_node->address = ft_strdup((char *)address);
		new_node->removed = false;
		new_node->next = NULL;
		
		// Find the last node
		while (contacts->next != NULL)
			contacts = contacts->next;
		
		// Add the new node
		contacts->next = new_node;
		
		return head;
	}
}

t_bool		remove_contact(Contact *contacts, int id)
{
	if (contacts == NULL)
		return false;

	Contact	*current = contacts;

	while (current != NULL)
	{
		if (current->id == id && !current->removed)
		{
			current->removed = true;
			return true;
		}
		current = current->next;
	}

	return false;
}

static t_bool	is_valid_id(Contact *contacts, int	id)
{
	if (id < 0)
		return false;

	Contact	*current = contacts;
	while (current)
	{
		if (current->id == id && !current->removed)
		{
			ft_printf("Error: Contact with ID %d already exists.\n", id);
			return false;
		}
		current = current->next;
	}

	return true;
}

// Check if phone contains at least one digit and only valid characters
t_bool is_valid_phone(const char *phone)
{
	if (!phone || *phone == '\0')
		return false;
		
	t_bool has_digit = false;
	while (*phone)
	{
		if (ft_isdigit(*phone))
			has_digit = true;
		else if (*phone != '+' && *phone != '-' && *phone != '(' && *phone != ')' && 
				*phone != ' ' && *phone != '.' && *phone != '/')
			return false;
		phone++;
	}
	
	return has_digit;
}

// Check if email has proper format with @ and domain with dot
t_bool is_valid_email(const char *email)
{
	if (!email || *email == '\0')
		return false;
		
	// Find the @ symbol
	const char *at_pos = ft_strchr(email, '@');
	if (!at_pos || at_pos == email) // No @ or @ is the first character
		return false;
		
	// Check domain part
	const char *domain = at_pos + 1;
	if (*domain == '\0') // Empty domain
		return false;
		
	// Check for dot in domain
	const char *dot_pos = ft_strchr(domain, '.');
	if (!dot_pos || dot_pos == domain || *(dot_pos + 1) == '\0')
		return false;
		
	return true;
}

t_bool update_contact(Contact *contacts, int id, const char *new_name, const char *new_phone, const char *new_email, const char *new_city, const char *new_address)
{
	if (!contacts || !new_name || !new_phone || !new_email || !new_city || !new_address)
		return false;
		
	// Validate the inputs
	if (ft_strlen(new_name) == 0 || ft_strlen(new_city) == 0)
		return false;
		
	if (!is_valid_phone(new_phone) || !is_valid_email(new_email))
		return false;
	
	// Find the contact with the given ID
	Contact *current = contacts;
	while (current)
	{
		if (current->id == id && !current->removed)
		{
			// Free existing memory
			free(current->name);
			free(current->phone);
			free(current->email);
			free(current->city);
			free(current->address);
			
			// Assign new values
			current->name = ft_strdup((char *)new_name);
			current->phone = ft_strdup((char *)new_phone);
			current->email = ft_strdup((char *)new_email);
			current->city = ft_strdup((char *)new_city);
			current->address = ft_strdup((char *)new_address);
			
			// Verify allocation succeeded
			if (!current->name || !current->phone || !current->email || 
				!current->city || !current->address)
				return false;
				
			return true;
		}
		current = current->next;
	}
	
	return false;
}
