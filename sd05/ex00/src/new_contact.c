#include "contact_manager.h"

static t_bool	is_valid_id(Contact *contacts, int	id);

Contact		*add_contact(Contact *contacts, int id, const char *name, const char *phone, const char *email, const char *city, const char *address)
{
	if (!is_valid_id(contacts, id) || !name || !phone || !email || !city || !address)
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