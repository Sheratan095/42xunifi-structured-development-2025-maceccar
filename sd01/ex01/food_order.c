#include "food_order.h"

int		process_food_order(struct OrderRequest *request)
{
	if (!request)
		return -1;

	// The check should be done considering the desired_arrive_datetime
	// and not the order_datetime
	if (check_restaurant_status(request))
	{
		OrderConfirmation	*conf = create_confirmation(request);
		send_confirmation_notification(conf);
		free_OrderConfirmation(conf);
		return (1);
	}

	return -1;
}

// factory based on desired_arrive_datetime
struct OrderConfirmation	*create_confirmation(struct OrderRequest *request)
{
	// means it's pre-orderd
	if (request->desired_arrive_datetime != NULL)
		return create_preorder_confirmation();

	return create_standard_confirmation();
}

void	free_OrderConfirmation(OrderConfirmation *conf)
{
	if (!conf)
		return ;

	free(conf);
}