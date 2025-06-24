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

	// if (save(argv[1], contacts) == false)
	// 	ft_printf("Contacts saved successfully to %s\n", argv[1]);
	// else
	// 	ft_printf("Error saving contacts to file: %s\n", argv[1]);

	free_contacts(contacts);
}

void	prompt(Contact *contacts)
{
	char	*input = NULL;
	int		choice = -1;

	do
	{
		ft_printf("Enter command (or type '%s' to save and exit): ", EXIT_COMMAND);
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

		switch (choice)
		{
			// case 0:
			// 	show_all_contacts(contacts);
			// 	break;

			case 1:
				printf("Enter name to search: \n");
				char	*name_query = get_next_line(0, false);
				printf("Searching for contacts with name: %s\n", name_query);

			default:
				break;
		}

	}
	while (ft_strncmp(input, EXIT_COMMAND, ft_strlen(EXIT_COMMAND)) != 0);

	free(input);
	get_next_line(0, true);
}
