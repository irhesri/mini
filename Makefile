
NAME	= mini
DIR = ./mini_imane/
SRCS		= ./mini_imane/env.c ./mini_imane/functions.c ./mini_imane/initialisation.c \
			./mini_imane/main.c  ./mini_imane/execution.c ./mini_imane/functions_2.c\
			./mini_imane/is_functions.c ./mini_imane/new_split.c ./mini_imane/trash_can.c \
			./mini_imane/expand.c ./mini_imane/global.c ./mini_imane/libft.c         \
			./mini_imane/not_builtin.c ./mini_imane/unset.c ./mini_imane/export.c\
			./mini_imane/history.c ./mini_imane/list_functions.c ./mini_imane/parsing.c\
SRC	= ./mini_imane/*.c ./mini_saida/*.c
# SRCS= env.c functions.c initialisation.c \
#  			main.c  execution.c functions_2.c\
#  			is_functions.c new_split.c trash_can.c \
#  			expand.c global.c libft.c         \
#  			not_builtin.c unset.c export.c\
#  			history.c list_functions.c parsing.c\
# SRC = $(SRCS:%.c=$(DIR)/%.c)
CFLAGS = -lreadline -g -fsanitize=address #-Wall -Wextra -Werror 
LDFLAGS		= -L ~/readline/usr/local/lib
CPPFLAGS	= -I ~/readline/usr/local/include

CC = gcc



all: 
	gcc ./mini_imane/*.c ./mini_saida/*.c $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) 
$(NAME): $(SRC:.c=.o) $(lib:.c=.o)
	$(CC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) -o $@ -c $<
bonus: $(SRC_B:.c=.o) $(lib:.c=.o)


%.o : %.c
	$(CC) $(LDFLAGS) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

clean:
	@rm -rf mini_imane/*.o

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re