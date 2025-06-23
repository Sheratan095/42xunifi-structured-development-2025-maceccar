#ifndef EXPENSE_TRACKER_BONUS_H
#define EXPENSE_TRACKER_BONUS_H

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
	Type	category;

	bool	removed;
	Expense *next; // Pointer to the next expense in the linked list, default is NULL
} Expense;

typedef struct ExpenseList
{
	Expense *head;
	int		current_id;
} ExpenseList;

bool		prompt(ExpenseList *expense_list);

//-------------------INITIALIZATION-------------------//

ExpenseList	*load_expenses(const char *filename);

bool	is_line_valid(const char *line);

bool	is_amount_valid(float amount);

Expense	*new_expense(ExpenseList *expense_list, int id, const char *description, float amount, const char *date, Type type);

bool	save_expenses(const ExpenseList *expense_list, const char *filename);

bool	update_expense(ExpenseList *expense_list, int id, const char *new_description, float new_amount, const char *new_date, Type new_type);

//-------------------SEARCHING-------------------//

ExpenseList	*search(Expense *expense_list, SearchMethod method, const char *query);

ExpenseList	*search_by_description(Expense *expense_list, const char *description);

ExpenseList	*search_by_date(Expense *expense_list, const char *date);

ExpenseList	*search_by_amount(Expense *expense_list, float amount);

ExpenseList	*search_by_type(Expense *expense_list, Type type);

ExpenseList	*search_by_daterange(Expense *expense_list, Type type);

ExpenseList	*search_by_category(Expense *expense_list, Type type);

//-------------------SHOWING-------------------//

void	display_expenses(Expense *expense_list); // in ascending order by id

void	show_expenses(Expense *expense_list);

int		count_expenses(Expense *expense_list);

float	calculate_total(Expense *expense_list);

float	calculate_average(Expense *expense_list);

void	show_category_breakdown(Expense *expense_list);

//-------------------CLEANING-------------------//

void	free_expenses(Expense *expense_list);

void	free_expense(Expense *expense);

bool	remove_expense(ExpenseList *expense_list, int id);

#endif