NAME		= contact_manager

COREKIT_PATH = ./corekit

VALGRIND =  valgrind --leak-check=full --track-origins=yes --track-fds=yes --show-leak-kinds=all

INCLUDES = -I./includes -I$(COREKIT_PATH)/includes

SRC = src/main.c \
		src/contact_manager.c \
		src/contact_loading.c \
		src/new_contact.c \
		src/cleanup.c \
		src/searching.c \

FLAGS	= -g
# FLAGS	+= -Wall -Werror -Wextra

$(NAME): $(SRC)
	@$(MAKE) -sC $(COREKIT_PATH)
	@cc $(SRC) $(INCLUDES) $(FLAGS) -L$(COREKIT_PATH) -lcorekit -o $(NAME)
	@echo "$(GREEN)[$(NAME)]:\t PROJECT COMPILED$(RESET)"

all:$(NAME)

clean:
	@${MAKE} -sC $(COREKIT_PATH) clean
	@echo "$(RED)[$(NAME)]:\t CLEAN$(RESET)"; \

fclean: clean
	@${MAKE} -sC $(COREKIT_PATH) fclean
	@rm -f $(NAME)
	@echo "$(RED)[$(NAME)]:\t FCLEAN$(RESET)"; \


re: fclean all

ARGS = test.csv

test: all
	./$(NAME) $(ARGS)

val: all
	$(VALGRIND) ./$(NAME) $(ARGS)

#COLORS

GREEN=\033[0;32m
RED=\033[0;31m
BLUE=\033[0;34m
RESET=\033[0m