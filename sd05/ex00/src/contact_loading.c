#include "contact_manager.h"

// Function prototypes for validation helpers
static char		**parse_csv_line(char *line);
static void		free_fields(char **fields);
static t_bool	validate_contact_fields(char **fields);
static t_bool	is_valid_id(const char *id_str);
static t_bool	is_valid_phone(const char *phone);
static t_bool	is_valid_email(const char *email);
static void		print_warning(const char *warning, const char *line, int line_number);

Contact		*load_contacts(const char *filename)
{
	Contact	*contacts = NULL;
	int		line_number = 0;

	if (!check_file_extension(filename))
		return NULL;

	int	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error: Could not open file '%s'\n", filename);
		return NULL;
	}

	char	*line;
	while ((line = get_next_line(fd, false)) != NULL)
	{
		line_number++;
		
		// Skip empty lines
		if (*line == '\0' || *line == '\n')
		{
			free(line);
			continue;
		}

		// Parse the line into contact fields
		char	**fields = parse_csv_line(line);

		if (!fields)
		{
			print_warning("Invalid CSV format", line, line_number);
			free(line);
			continue;
		}

		if (validate_contact_fields(fields))
		{
			// Create and add a new contact if valid
			Contact *new_contacts = add_contact(
				contacts,
				ft_atoi(fields[0]),
				fields[1],
				fields[2],
				fields[3],
				fields[4],
				fields[5]
			);
			
			if (new_contacts)
				contacts = new_contacts;

		}
		else
		{
			print_warning("Invalid contact data", line, line_number);
		}
		
		// Free memory
		free_fields(fields);
		free(line);
	}
	
	get_next_line(fd, true);
	close(fd);

	return contacts;
}

t_bool		check_file_extension(const char *filename)
{
	if (ft_str_end_with_str(filename, TARGET_FILE_EXTENSION) == false)
	{
		ft_printf("Error: File must have a '%s' extension.\n", TARGET_FILE_EXTENSION);
		return false;
	}

	return true;
}

// Helper function to parse CSV line into fields
static char	**parse_csv_line(char *line)
{
	char	**fields = malloc(sizeof(char *) * 7); // 6 fields + NULL terminator
	if (!fields)
		return NULL;
	
	int		field_count = 0;
	char	*start = line;
	char	*end;
	
	// Parse each comma-separated field
	while (*start && field_count < 6)
	{
		// Find next comma or end of string
		end = start;
		while (*end && *end != ',')
			end++;
			
		// Temporary null terminator to extract field
		t_bool	is_end = (*end == '\0');
		*end = '\0';
		
		// Trim whitespace and store field
		fields[field_count++] = ft_strtrim(start, " \t\n\r", false);
		
		if (is_end)
			break;
			
		// Move to next field
		start = end + 1;
	}
	
	// Check if we got exactly 6 fields
	if (field_count != 6)
	{
		free_fields(fields);
		return NULL;
	}
	
	fields[6] = NULL;
	return fields;
}

// Validate fields of a contact
static t_bool	validate_contact_fields(char **fields)
{
	// Check ID is valid positive integer
	if (!is_valid_id(fields[0]))
		return false;
		
	int id = ft_atoi(fields[0]);
	if (id <= 0)
		return false;
		
	// Check name and city are non-empty after trimming
	if (ft_strlen(fields[1]) == 0 || ft_strlen(fields[4]) == 0)
		return false;
	
	// Check phone format
	if (!is_valid_phone(fields[2]))
		return false;
		
	// Check email format
	if (!is_valid_email(fields[3]))
		return false;
		
	// Address may be empty (no validation needed)
	
	return true;
}

// Check if string represents a valid integer
static t_bool	is_valid_id(const char *id_str)
{
	if (!id_str || *id_str == '\0')
		return false;
		
	// Check if it's all digits
	while (*id_str)
	{
		if (!ft_isdigit(*id_str))
			return false;
		id_str++;
	}
	
	return true;
}

// Check if phone contains at least one digit and only valid characters
static t_bool	is_valid_phone(const char *phone)
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
static t_bool	is_valid_email(const char *email)
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

// Free memory allocated for fields
static void	free_fields(char **fields)
{
	if (!fields)
		return;
		
	for (int i = 0; fields[i]; i++)
		free(fields[i]);
		
	free(fields);
}

static void	print_warning(const char *warning, const char *line, int line_number)
{
	ft_printf("Warning: %s on line %d: '%s'\n", warning, line_number, line);
}
