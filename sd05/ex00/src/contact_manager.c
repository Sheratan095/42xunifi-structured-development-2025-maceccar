#include "contact_manager.h"

t_bool		save(const char *filename, Contact *contacts)
{
	int	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return false;

	Contact *current = contacts;
	while (current)
	{
		if (!current->removed)
		{
			// Convert ID to string, but free it after use
			char *id_str = ft_itoa(current->id);
			
			// Write the contact data
			ft_putstr_fd(id_str, fd);
			ft_putchar_fd(',', fd);
			ft_putstr_fd(current->name, fd);
			ft_putchar_fd(',', fd);
			ft_putstr_fd(current->phone, fd);
			ft_putchar_fd(',', fd);
			ft_putstr_fd(current->email, fd);
			ft_putchar_fd(',', fd);
			ft_putstr_fd(current->city, fd);
			ft_putchar_fd(',', fd);
			ft_putstr_fd(current->address ? current->address : "", fd);
			ft_putchar_fd('\n', fd);
			
			// Free the id_str to prevent leak
			free(id_str);
		}
		current = current->next;
	}

	close(fd);
	return true;
}

void	show_all_contacts(Contact *contacts)
{
	if (!contacts)
	{
		ft_printf("No contacts available.\n");
		return ;
	}

	ft_printf("ID\tName\tPhone\tEmail\tCity\tAddress\n");
	ft_printf("---------------------------------------------\n");

	while (contacts)
	{
		if (!contacts->removed)
		{
			ft_printf("%d\t\t\t%s\t\t\t%s\t\t%s\t\t\t%s\t\t\t%s\n",
				contacts->id,
				contacts->name,
				contacts->phone,
				contacts->email,
				contacts->city,
				contacts->address ? contacts->address : "N/A");
		}
		contacts = contacts->next;
	}
}