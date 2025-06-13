#ifndef FOOD_ORDER_H
#define FOOD_ORDER_H

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Assuming datetime is a string well formatted

typedef struct FoodItem
{
	int		food_id;
	char	*name;
	char	*description;
	bool	available;
} FoodItem;

typedef struct Restaurant
{
	char		*name;
	bool		open;
	char		*address;
	char		*phone_number;
	FoodItem	available_food[512];
} Restaurant;

typedef struct OrderedFood
{
	FoodItem	*food;
	int			amount;
} OrderedFood;

typedef struct OrderRequest
{
	bool		pre_ordered;
	char		*order_datetime;
	char		*desired_arrive_datetime;
	Restaurant	*restaurant;
	OrderedFood	ordered_food[64];
} OrderRequest;

typedef struct OrderConfirmation
{
	OrderRequest	*request;
	OrderedFood		confirmed_food[64];
	char			*estimated_arrive_datetime;
} OrderConfirmation;

// Checks if the restaurant is open based on the order. Returns 1 if open, 0 if closed.
int	check_restaurant_status(struct OrderRequest *request);

// Creates a confirmation for an immediate order. Returns NULL on failure.
struct OrderConfirmation	*create_standard_confirmation(void);

// Creates a confirmation for a future (pre-order). Returns NULL on failure.
struct OrderConfirmation	*create_preorder_confirmation(void);

// Sends the confirmation to the user.
void	send_confirmation_notification(struct OrderConfirmation *confirmation);

int		process_food_order(struct OrderRequest *request);

struct OrderConfirmation	*create_confirmation(struct OrderRequest *request);

void	free_OrderConfirmation(OrderConfirmation *conf);

#endif