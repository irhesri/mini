NAME = mini
CFLAGS = -L /Users/sben-chi/.brew/opt/readline/lib -I /Users/sben-chi/.brew/opt/readline/include 
CC = gcc

MANDATORY_PART = test.c heredoc.c


M_OFILES = ${MANDATORY_PART:.c=.o}

all: $(NAME)

$(NAME): $(M_OFILES)
	$(CC) $(M_OFILES) -o $(NAME) -lreadline $(CFLAGS)
	
re: fclean all

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(M_OFILES)
