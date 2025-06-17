#include "password_validator.h"
#include <stdio.h>

static bool	are_similar(const char *s1, const char *s2);
static int	ft_abs(int n);

PwStatus	validate_password(const char *new_pw, PasswordHistory *history)
{
	bool	has_lowercase = false;
	bool	has_uppercase = false;
	bool	has_digit = false;
	bool	has_special_char = false;
	int		i = 0;

	if (new_pw == NULL || history == NULL)
		return INVALID;

	for (int j = 0; j < 3; j++)
	{
		if (history->passwords[j] != NULL && are_similar(new_pw, history->passwords[j]))
			return INVALID;
	}

	while (new_pw[i])
	{
		if (is_digit(new_pw[i]))
			has_digit = true;
		else if (is_lowercase(new_pw[i]))
			has_lowercase = true;
		else if (is_uppercase(new_pw[i]))
			has_uppercase = true;
		else if (is_special_char(new_pw[i]))
			has_special_char = true;
		i++;
	}

	if (!has_digit || !has_lowercase ||
			!has_uppercase || !has_special_char || i < 8)
		return INVALID;

	// if (history->passwords[0] != NULL)
	// 		free(history->passwords[0]); // free the oldest password if it exists

	// shift to left the passwords in history
	return VALID;
}

void	add_pw_to_history(PasswordHistory *history, char *new_pw)
{
	if (history == NULL || new_pw == NULL)
		return ;

	if (history->count < 3)
	{
		history->passwords[history->count] = new_pw;
		history->count++;
		return ;
	}

	history->passwords[0] = history->passwords[1];
	history->passwords[1] = history->passwords[2];
	history->passwords[2] = new_pw;
}

//Similarity rule:
// • The new password must not have an edit distance less or equal than one from
// 		any of the last three chosen passwords.
static bool	are_similar(const char *s1, const char *s2)
{
	int	i;
	int	j;
	int	len1 = ft_strlen(s1);
	int	len2 = ft_strlen(s2);
	int	diff = 0;

	// If lengths differ by more than 1, edit distance is at least 2
	if (ft_abs(len1 - len2) > 1)
		return false;
	
	// Case 1: Same length - check for one character substitution
	if (len1 == len2)
	{
		for (i = 0; i < len1; i++)
		{
			if (s1[i] != s2[i])
				diff++;
			if (diff > 1)
				return false;
		}

		// If we reach here, diff is either 0 (identical) or 1 (one substitution)
		return true;
	}

	// Case 2: Different lengths - check for one insertion/deletion
	const char	*longer = (len1 > len2) ? s1 : s2;
	const char	*shorter = (len1 > len2) ? s2 : s1;
	int longer_len = (len1 > len2) ? len1 : len2;
	int shorter_len = (len1 > len2) ? len2 : len1;
	
	i = 0;  // index for longer string
	j = 0;  // index for shorter string
	
	while (i < longer_len && j < shorter_len)
	{
		if (longer[i] != shorter[j])
		{
			// Skip this character in the longer string
			i++;
			diff++;
			if (diff > 1)
				return false;
		}
		else
		{
			// Characters match, advance both indices
			i++;
			j++;
		}
	}
	
	// If we reach here, the strings are similar (edit distance <= 1)
	return true;
}

static int ft_abs(int n)
{
	return (n < 0) ? -n : n;
}

// static void print_test_result(const char* test_name, bool passed) {
// 	printf("%-40s : %s\n", test_name, passed ? "PASSED" : "FAILED");
// }

// int main()
// {
// 	printf("=== Testing Password Similarity ===\n");
	
// 	// Test identical passwords
// 	print_test_result("Identical passwords", 
// 					  are_similar("Password123!", "Password123!") == true);
	
// 	// Test one character different
// 	print_test_result("One character substitution", 
// 					  are_similar("Password123!", "Password124!") == true);
					  
// 	// Test one character added
// 	print_test_result("One character addition", 
// 					  are_similar("Password123!", "Password1234!") == true);
					  
// 	// Test one character removed
// 	print_test_result("One character removal", 
// 					  are_similar("Password123!", "Password12!") == true);
					  
// 	// Test two characters different (should not be similar)
// 	print_test_result("Two characters different", 
// 					  are_similar("Password123!", "Password643!") == false);
					  
// 	// Test two characters longer (should not be similar)
// 	print_test_result("Two characters longer", 
// 					  are_similar("Password123!", "Password123!AB") == false);
	
// 	printf("\n=== Testing Full Password Validation and History ===\n");
	
// 	// Create password history
// 	PasswordHistory history;
// 	// Initialize history
// 	for (int i = 0; i < 3; i++)
// 		history.passwords[i] = NULL;
// 	history.count = 0;
	
// 	// Add initial passwords to history
// 	char *pw1 = ("OldPass123!");
// 	char *pw2 = ("Previous2#");
// 	char *pw3 = ("FirstOne3$");
	
// 	add_pw_to_history(&history, pw1);
// 	add_pw_to_history(&history, pw2);
// 	add_pw_to_history(&history, pw3);
	
// 	print_test_result("History initialization", 
// 					 history.count == 3 && 
// 					 history.passwords[0] == pw1 && 
// 					 history.passwords[1] == pw2 && 
// 					 history.passwords[2] == pw3);
	
// 	// Test valid password
// 	print_test_result("Valid password", 
// 					 validate_password("NewPassword4%", &history) == VALID);
	
// 	// Test too similar to history
// 	print_test_result("Too similar to history password", 
// 					 validate_password("FirstOne3$X", &history) == INVALID);
	
// 	// Test invalid passwords due to pattern requirements
// 	print_test_result("Too short", 
// 					 validate_password("Short1!", &history) == INVALID);
					  
// 	print_test_result("Missing uppercase", 
// 					 validate_password("password123!", &history) == INVALID);
					  
// 	print_test_result("Missing lowercase", 
// 					 validate_password("PASSWORD123!", &history) == INVALID);
					  
// 	print_test_result("Missing digit", 
// 					 validate_password("PasswordNoDigit!", &history) == INVALID);
					  
// 	print_test_result("Missing special character", 
// 					 validate_password("Password12345", &history) == INVALID);
	
// 	// Test history rotation (adding a 4th password)
// 	char *pw4 = ("NewerPass5^");
// 	add_pw_to_history(&history, pw4);
	
// 	print_test_result("History rotation", 
// 					 history.count == 3 && 
// 					 history.passwords[0] == pw2 && 
// 					 history.passwords[1] == pw3 && 
// 					 history.passwords[2] == pw4);
	
// 	return 0;
// }