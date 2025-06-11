#ifndef PASSWORD_VALIDATOR_H
#define PASSWORD_VALIDATOR_H

#include <stddef.h>
#include <stdbool.h>

typedef enum PwStatus
{
	VALID,
	INVALID
} PwStatus;


PwStatus	validate_password(const char *new_pw, const char *curr_pw);

#endif