#include "password_validator.h"
#include <stdio.h>

// PwStatus	validate_password(const char *new_pw, const char *curr_pw)
// {
// 	bool	differ_from_current = false;
// 	bool	has_lowercase = false;
// 	bool	has_uppercase = false;
// 	bool	has_digit = false;
// 	bool	has_special_char = false;
// 	int		i = 0;

// 	if (new_pw == NULL || curr_pw == NULL)
// 		return INVALID;

// 	differ_from_current = !(ft_strcmp(new_pw, curr_pw));

// 	while (new_pw[i])
// 	{
// 		if (is_digit(new_pw[i]))
// 			has_digit = true;
// 		else if (is_lowercase(new_pw[i]))
// 			has_lowercase = true;
// 		else if (is_uppercase(new_pw[i]))
// 			has_uppercase = true;
// 		else if (is_special_char(new_pw[i]))
// 			has_special_char = true;
// 		i++;
// 	}

// 	if (!differ_from_current || !has_digit || !has_lowercase ||
// 			!has_uppercase || !has_special_char || i < 8)
// 		return INVALID;
	
// 	return VALID;
// }

bool	ft_strcmp(const char *s1, const char *s2)
{
	int	i = 0;
	int	len = ft_strlen(s1);

	if (len != ft_strlen(s2))
		return false;

	while (i < len)
	{
		if (s1[i] != s2[i])
			return false;
		i++;
	}
	return true;
}

bool	is_digit(const char c)
{
	return (c >= '0' && c <= '9');
}

bool	is_lowercase(const char c)
{
	return (c >= 'a' && c <= 'z');
}

bool	is_uppercase(const char c)
{
	return (c >= 'A' && c <= 'Z');
}

bool	is_special_char(const char c)
{
	return (c == '@' || c == '#' || c == '$' || c == '%' || c == '^' || c == '&' || c == '*');
}

int	ft_strlen(const char *str)
{
	int len = 0;
	while (str[len] != '\0')
		len++;
	return len;
}

// int main(void)
// {
// 	printf("===== Password Validator Tests =====\n\n");
	
// 	// Test case 1: Valid password
// 	const char *test1_new = "Password1@";
// 	const char *test1_curr = "OldPass2#";
// 	PwStatus result1 = validate_password(test1_new, test1_curr);
// 	printf("Test 1 (Valid password): %s\n", result1 == VALID ? "PASS" : "FAIL");
	
// 	// Test case 2: Too short
// 	const char *test2_new = "Pass1@";
// 	const char *test2_curr = "OldPass2#";
// 	PwStatus result2 = validate_password(test2_new, test2_curr);
// 	printf("Test 2 (Too short): %s\n", result2 == INVALID ? "PASS" : "FAIL");
	
// 	// Test case 3: No lowercase
// 	const char *test3_new = "PASSWORD1@";
// 	const char *test3_curr = "OldPass2#";
// 	PwStatus result3 = validate_password(test3_new, test3_curr);
// 	printf("Test 3 (No lowercase): %s\n", result3 == INVALID ? "PASS" : "FAIL");
	
// 	// Test case 4: No uppercase
// 	const char *test4_new = "password1@";
// 	const char *test4_curr = "OldPass2#";
// 	PwStatus result4 = validate_password(test4_new, test4_curr);
// 	printf("Test 4 (No uppercase): %s\n", result4 == INVALID ? "PASS" : "FAIL");
	
// 	// Test case 5: No digit
// 	const char *test5_new = "Password@";
// 	const char *test5_curr = "OldPass2#";
// 	PwStatus result5 = validate_password(test5_new, test5_curr);
// 	printf("Test 5 (No digit): %s\n", result5 == INVALID ? "PASS" : "FAIL");
	
// 	// Test case 6: No special char
// 	const char *test6_new = "Password12";
// 	const char *test6_curr = "OldPass2#";
// 	PwStatus result6 = validate_password(test6_new, test6_curr);
// 	printf("Test 6 (No special char): %s\n", result6 == INVALID ? "PASS" : "FAIL");
	
// 	// Test case 7: Same as current
// 	const char *test7_new = "OldPass2#";
// 	const char *test7_curr = "OldPass2#";
// 	PwStatus result7 = validate_password(test7_new, test7_curr);
// 	printf("Test 7 (Same as current): %s\n", result7 == INVALID ? "PASS" : "FAIL");
	
// 	// Test case 8: NULL inputs
// 	PwStatus result8a = validate_password(NULL, "OldPass2#");
// 	PwStatus result8b = validate_password("Password1@", NULL);
// 	PwStatus result8c = validate_password(NULL, NULL);
// 	printf("Test 8 (NULL inputs): %s\n", 
// 		   (result8a == INVALID && result8b == INVALID && result8c == INVALID) ? "PASS" : "FAIL");
	
// 	return 0;
// }