#include "contact_manager.h"

int	main(int argc, char **argv)
{
	Contact	*contacts = NULL;

	if (argc < 2)
	{
		ft_printf("Usage: %s <filename>\n", argv[0]);
		return 1;
	}

	contacts = load_contacts(argv[1]);
	if (!contacts)
	{
		ft_printf("Error loading contacts from file: %s\n", argv[1]);
		return 1;
	}

	prompt(contacts);

	if (save(argv[1], contacts))
		ft_printf("Contacts saved successfully to %s\n", argv[1]);
	else
		ft_printf("Error saving contacts to file: %s\n", argv[1]);

	free_contacts(contacts);
}

void	prompt(Contact *contacts)
{
	char	*input = NULL;
	int		choice = -1;
	t_bool	exit_command = false;

	do
	{
		ft_printf("\nEnter command (or type '%s' to save and exit):\n", EXIT_COMMAND);
		ft_printf("0: list all contacts\n");
		ft_printf("1: search by name\n");
		ft_printf("2: search by city\n");
		ft_printf("3: add a new contact\n");
		ft_printf("4: edit a contact\n");
		ft_printf("5: remove a contact\n\n");
	
		input = get_next_line(0, false);
		if (!input)
			return ;

		choice = ft_atoi(input);

		if (ft_strncmp(input, EXIT_COMMAND, ft_strlen(EXIT_COMMAND)) == 0)
			exit_command = true;
		else
		{
			switch (choice)
			{
				case 0:
					show_all_contacts(contacts);
					break;

				case 1:
					ft_printf("Enter name to search: \n");
					char	*name_query = get_next_line(0, false);

					search_by_name(contacts, name_query);
					free(name_query);
					break;

				case 2:
					ft_printf("Enter city to search: \n");
					char	*city_query = get_next_line(0, false);

					search_by_city(contacts, city_query);
					free(city_query);
					break;

				case 3:
					{
						ft_printf("Enter new contact details:\n");
						
						// Find the maximum ID in the existing contacts
						int	max_id = 0;
						Contact *temp = contacts;
						while (temp) {
							if (temp->id > max_id) {
								max_id = temp->id;
							}
							temp = temp->next;
						}
						
						// New ID will be max_id + 1
						int new_id = max_id + 1;
						ft_printf("ID will be set to: %d\n", new_id);
						
						// Get name
						ft_printf("Name: ");
						char *name_input = get_next_line(0, false);
						char *name = ft_strtrim(name_input, "\n\r", false);
						free(name_input);
						
						// Get phone
						ft_printf("Phone: ");
						char *phone_input = get_next_line(0, false);
						char *phone = ft_strtrim(phone_input, "\n\r", false);
						free(phone_input);
						
						// Get email
						ft_printf("Email: ");
						char *email_input = get_next_line(0, false);
						char *email = ft_strtrim(email_input, "\n\r", false);
						free(email_input);
						
						// Get city
						ft_printf("City: ");
						char *city_input = get_next_line(0, false);
						char *city = ft_strtrim(city_input, "\n\r", false);
						free(city_input);
						
						// Get address
						ft_printf("Address: ");
						char *address_input = get_next_line(0, false);
						char *address = ft_strtrim(address_input, "\n\r", false);
						free(address_input);
						
						// Add the new contact
						Contact *new_contacts = add_contact(contacts, new_id, name, phone, email, city, address);
						
						if (new_contacts)
						{
							contacts = new_contacts;
							ft_printf("Contact added successfully.\n");
						}
						else
						{
							ft_printf("Failed to add contact. Please check your input.\n");
						}
						
						// Free allocated memory
						free(name);
						free(phone);
						free(email);
						free(city);
						free(address);
					}
					break;

				case 4:
					{
						ft_printf("Enter ID of contact to edit: \n");
						char *edit_id_input = get_next_line(0, false);
						int id_to_edit = ft_atoi(edit_id_input);
						free(edit_id_input);
						
						// Check if contact with this ID exists
						Contact *temp = contacts;
						t_bool found = false;
						while (temp) {
							if (temp->id == id_to_edit && !temp->removed) {
								found = true;
								break;
							}
							temp = temp->next;
						}
						
						if (!found) {
							ft_printf("Error: Contact with ID %d not found.\n", id_to_edit);
							break;
						}
						
						ft_printf("Editing contact with ID %d\n", id_to_edit);
						ft_printf("Enter new information (leave blank to keep current value):\n");
						
						// Get new name
						ft_printf("Name [%s]: ", temp->name);
						char *name_input = get_next_line(0, false);
						char *new_name = ft_strtrim(name_input, "\n\r", false);
						free(name_input);
						
						// Get new phone
						ft_printf("Phone [%s]: ", temp->phone);
						char *phone_input = get_next_line(0, false);
						char *new_phone = ft_strtrim(phone_input, "\n\r", false);
						free(phone_input);
						
						// Get new email
						ft_printf("Email [%s]: ", temp->email);
						char *email_input = get_next_line(0, false);
						char *new_email = ft_strtrim(email_input, "\n\r", false);
						free(email_input);
						
						// Get new city
						ft_printf("City [%s]: ", temp->city);
						char *city_input = get_next_line(0, false);
						char *new_city = ft_strtrim(city_input, "\n\r", false);
						free(city_input);
						
						// Get new address
						ft_printf("Address [%s]: ", temp->address);
						char *address_input = get_next_line(0, false);
						char *new_address = ft_strtrim(address_input, "\n\r", false);
						free(address_input);
						
						// Use empty inputs to keep current values
						if (ft_strlen(new_name) == 0) {
							free(new_name);
							new_name = ft_strdup(temp->name);
						}
						
						if (ft_strlen(new_phone) == 0) {
							free(new_phone);
							new_phone = ft_strdup(temp->phone);
						}
						
						if (ft_strlen(new_email) == 0) {
							free(new_email);
							new_email = ft_strdup(temp->email);
						}
						
						if (ft_strlen(new_city) == 0) {
							free(new_city);
							new_city = ft_strdup(temp->city);
						}
						
						if (ft_strlen(new_address) == 0) {
							free(new_address);
							new_address = ft_strdup(temp->address);
						}
						
						// Update the contact
						if (update_contact(contacts, id_to_edit, new_name, new_phone, new_email, new_city, new_address))
							ft_printf("Contact updated successfully.\n");
						else
							ft_printf("Failed to update contact. Please check your input.\n");
						
						// Free allocated memory
						free(new_name);
						free(new_phone);
						free(new_email);
						free(new_city);
						free(new_address);
					}
					break;

				case 5:
					ft_printf("Enter ID of contact to remove: \n");

					char	*remove_id = get_next_line(0, false);
					int		id_to_remove = ft_atoi(remove_id);

					if (remove_contact(contacts, id_to_remove))
						ft_printf("Contact with ID %d removed successfully.\n", id_to_remove);
					else
						ft_printf("Error removing contact with ID %d.\n", id_to_remove);

					free(remove_id);
					break;

				default:
					ft_printf("Invalid command. Please try again.\n");
					break;
			}
		}
		free(input);
	}
	while (exit_command == false);

	// Clean up get_next_line resources
	get_next_line(0, true);
}
