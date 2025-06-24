#include "contact_manager.h"

void		free_contacts(Contact *contacts)
{
	Contact	*current = contacts;
	Contact	*next;

	while (current != NULL)
	{
		next = current->next;
		free_contact(current);
		current = next;
	}
}

void		free_contact(Contact *contact)
{
	if (!contact)
		return;

	free(contact->name);
	free(contact->phone);
	free(contact->email);
	free(contact->city);
	free(contact->address);
	free(contact);
}