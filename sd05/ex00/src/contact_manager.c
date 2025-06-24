#include "contact_manager.h"

t_bool		save(const char *filename, Contact *contacts)
{
	int	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return false;

	while ((contacts != NULL))
	{
		write(fd, ft_itoa(contacts->id), ft_strlen(ft_itoa(contacts->id)));
		write(fd, ",", 1);
		write(fd, contacts->name, ft_strlen(contacts->name));
		write(fd, ",", 1);
		write(fd, contacts->phone, ft_strlen(contacts->phone));
		write(fd, ",", 1);
		write(fd, contacts->email, ft_strlen(contacts->email));
		write(fd, ",", 1);
		write(fd, contacts->city, ft_strlen(contacts->city));
		write(fd, ",", 1);
		write(fd, contacts->address, ft_strlen(contacts->address));
		write(fd, "\n", 1);

		contacts = contacts->next;
	}

	close(fd);
	return true;
}