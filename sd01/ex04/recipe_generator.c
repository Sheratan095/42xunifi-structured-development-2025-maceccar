
#include "recipe_generator.h"

struct Recipe	*create_custom_recipe(void)
{
	Ingredients	*ingredients = get_current_ingredients();
	if (!ingredients)
		return NULL;

	TasteProfile	*taste = get_user_taste_profile();
	if (!taste)
	{
		free_ingredients(ingredients);
		return NULL;
	}

	Recipe	*current_recipe = NULL;
	do
	{
		if (current_recipe != NULL)
			free_recipe(current_recipe);

		current_recipe = create_recipe(ingredients, taste);
		if (!current_recipe)
		{
			free_ingredients(ingredients);
			free_taste_profile(taste);
			return NULL;
		}

	} while (get_user_approval(current_recipe) == 0);

	free_ingredients(ingredients);
	free_taste_profile(taste);

	return current_recipe;
}

void	free_ingredient(struct Ingredient *ingredient)
{
	if (!ingredient)
		return;

	// free(ingredient->name);
	// free(ingredient->unit);
	// free(ingredient);
}