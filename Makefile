
NAME	= mini

SRC		= mini_imane/debugging.c mini_imane/expand.c mini_imane/functions.c mini_imane/list_functions.c mini_imane/minishell.h \
		mini_imane/parsing.c mini_imane/env.c mini_imane/export.c mini_imane/libft.c mini_imane/main.c mini_imane/new_split.c \
		mini_imane/unset.c

#CFLAGS = -Wall -Wextra -Werror

CC = gcc

all: $(NAME)

$(NAME): $(SRC:.c=.o) $(lib:.c=.o)
	$(CC)  -readline $(CFLAGS) -o $@ -c $<
bonus: $(SRC_B:.c=.o) $(lib:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -rf mini_imane/*.o

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re