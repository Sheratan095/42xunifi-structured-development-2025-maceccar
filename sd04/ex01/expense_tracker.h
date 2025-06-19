#ifndef EXPENSE_TRACKER_H
#define EXPENSE_TRACKER_H

#include <stdbool.h>

typedef struct Expense Expense;

typedef enum Type
{
	FOOD,
	BEVERAGES,
	TRANSPORT,
	CLOTHING,
} Type;

typedef enum SearchMethod
{
	SEARCH_BY_DESCRIPTION,
	SEARCH_BY_DATE,
	SEARCH_BY_AMOUNT,
	SEARCH_BY_TYPE,
} SearchMethod;

typedef struct Expense
{
	char	*description;
	float	amount;
	char	*date; // in YYYY-MM-DD format
	Type	type;
	Expense *next; // Pointer to the next expense in the linked list, default is NULL
} Expense;

//-------------------INITIALIZATION-------------------//

Expense	*load_expenses(const char *filename);

bool	is_line_valid(const char *line);

bool	is_date_valid(const char *date);

bool	is_amount_valid(float amount);

Expense	*new_expense(char *description, float amount, const char *date, Type type);

//-------------------SEARCHING-------------------//

Expense	*search(Expense *expenses, SearchMethod method, const char *query);

Expense	*search_by_description(Expense *expenses, const char *description);

Expense	*search_by_date(Expense *expenses, const char *date);

Expense	*search_by_amount(Expense *expenses, float amount);

Expense	*search_by_type(Expense *expenses, Type type);

//-------------------SHOWING-------------------//

void	show_expenses(Expense *expenses);

int		count_expenses(Expense *expenses);

float	calculate_total(Expense *expenses);

float	calculate_average(Expense *expenses);

void	show_category_breakdown(Expense *expenses);

//-------------------CLEANING-------------------//

void	free_expenses(Expense *expenses);

void	free_expense(Expense *expense);

#endif