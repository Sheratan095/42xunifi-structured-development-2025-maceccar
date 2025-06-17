#ifndef PASSWORD_VALIDATOR_H
#define PASSWORD_VALIDATOR_H

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef enum PwStatus
{
	VALID,
	INVALID
} PwStatus;

typedef struct PasswordHistory
{
	char	*passwords[3];
	int		count;
} PasswordHistory;

// PwStatus	validate_password(const char *new_pw, const char *curr_pw);

PwStatus	validate_password(const char *new_pw, PasswordHistory *history);

int		ft_strlen(const char *str);

bool	is_digit(const char c);

bool	is_lowercase(const char c);

bool	is_uppercase(const char c);

bool	is_special_char(const char c);

bool	ft_strcmp(const char *s1, const char *s2);

#endif