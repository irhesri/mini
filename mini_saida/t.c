#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>


int main()
{
	char *l;
	
	while(1)
	{
	l = readline("> ");
	sleep(3);
	rl_replace_line("> efhfefo> ");
	add_history(l);
	}
}
