NAME	= minishell

DIR1	= ./execution
DIR2	= ./parsing
DIR3	= ./others
DIR4	= ./builtins

SRC1	= execution.c not_builtin.c
SRC2	= expand.c initialisation.c parsing.c
SRC3	= functions.c functions_2.c global.c \
			is_functions.c libft.c list_functions.c \
			new_split.c trash_can.c	
SRC4	= history.c env.c export.c unset.c

SRCS	= main.c $(SRC1:%.c=$(DIR1)/%.c) \
			$(SRC2:%.c=$(DIR2)/%.c) $(SRC3:%.c=$(DIR3)/%.c) \
			$(SRC4:%.c=$(DIR4)/%.c)

OBJ		= $(SRCS:.c=.o)

CC 			= gcc 
CFLAGS		= -lreadline # -Wall -Wextra -Werror 
LDFLAGS		= -L /Users/sben-chi/.brew/opt/readline/lib
CPPFLAGS	= -I /Users/sben-chi/.brew/opt/readline/include
# LDFLAGS		= -L /Users/irhesri/readline/usr/local/lib
# CPPFLAGS	= -I /Users/irhesri/readline/usr/local/include

all: 
	gcc -lreadline ./mini_imane/*.c ./mini_saida/*.c $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) -g -fsanitize=address

# $(NAME): $(OBG)
# 	$(CC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) -o $@ -c $<

# %.o : %.c
# 	$(CC) $(LDFLAGS) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re