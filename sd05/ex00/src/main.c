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
