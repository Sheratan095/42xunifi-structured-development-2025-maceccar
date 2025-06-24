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

	if (save(argv[1], contacts) == true)
		ft_printf("Contacts saved successfully to %s\n", argv[1]);
	else
		ft_printf("Error saving contacts to file: %s\n", argv[1]);

}

t_bool	prompt(Contact *contacts)
{
	char	*input = NULL;

	while (ft_strcmp(input, EXIT_COMMAND) != 0)
	{
		ft_printf("Enter command (or type '%s' to save and exit): ", EXIT_COMMAND);

	}
}
