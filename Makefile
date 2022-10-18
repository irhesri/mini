NAME	= minishell

CC 			= gcc 
CFLAGS		= -Wall -Wextra -Werror -g# -fsanitize=address
LDFLAGS		= -L ~/.brew/opt/readline/lib
CPPFLAGS	= -I ~/.brew/opt/readline/include

SRC1	= execution.c heredoc.c not_builtin.c termios_signals.c in_out_files.c
SRC2	= expand.c parsing.c \
			redirection.c redirection_utils.c \
			parsing_utils.c
SRC3	= ft_atoi.c functions.c functions_2.c global.c \
			is_functions.c libft.c list_functions.c \
			new_split.c trash_can.c	
SRC4	= history.c env.c export.c unset.c \
			cd.c echo.c exit.c pwd.c

SRC		= main.c $(SRC1:%.c=./execution/%.c) \
			$(SRC2:%.c=./parsing/%.c) $(SRC3:%.c=./general_functions/%.c) \
			$(SRC4:%.c=./builtins/%.c)

OBJ		= $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(OBJ) -lreadline -o $(NAME)

%.o : %.c 
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re