NAME		= first_last

VALGRIND =  valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -q

SRC = *.c

FLAGS	= -g

$(NAME): $(SRC)
	@cc $(SRC) $(INCLUDES) $(FLAGS) -o $(NAME)
	@echo "$(GREEN)[$(NAME)]:\t PROJECT COMPILED$(RESET)"

all:$(NAME)

clean:

fclean: clean
	@rm -f $(NAME)

re: fclean all

args =

test: all
	 ./$(NAME) $(args)

val: all
	@$(VALGRIND) ./$(NAME) $(args)

#COLORS

GREEN=\033[0;32m
RED=\033[0;31m
BLUE=\033[0;34m
RESET=\033[0m