
NAME	= mini

# SRC		= mini_imane/debugging.c mini_imane/expand.c mini_imane/functions.c mini_imane/list_functions.c mini_imane/minishell.h \
# 		mini_imane/parsing.c mini_imane/env.c mini_imane/export.c mini_imane/libft.c mini_imane/main.c mini_imane/new_split.c \
# 		mini_imane/unset.c
SRC	= ./mini_imane/*.c ./mini_saida/*.c
#CFLAGS = -Wall -Wextra -Werror

NORME = ./mini_imane/commands_call.c ./mini_imane/expand.c ./mini_imane/global.c \
		./mini_imane/list_functions.c ./mini_imane/not_builtin.c ./mini_imane/trash_can.c \
		./mini_imane/export.c ./mini_imane/initialisation.c ./mini_imane/parsing.c \
		./mini_imane/unset.c ./mini_imane/env.c ./mini_imane/functions.c ./mini_imane/libft.c \
		./mini_imane/new_split.c ./mini_imane/functions_2.c

CC = gcc

all:
	gcc ./mini_imane/*.c ./mini_saida/*.c -lreadline -fsanitize=address

$(NAME): $(SRC:.c=.o) $(lib:.c=.o)
	$(CC)  -lreadline $(CFLAGS) -o $@ -c $<
bonus: $(SRC_B:.c=.o) $(lib:.c=.o)

norme:
	@norminette $(NORME)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -rf mini_imane/*.o

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re