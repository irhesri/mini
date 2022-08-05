#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// enum	builtins
// {
// 	echo = 1, pwd, cd,/* exit, */
// 	env, export, unset,
// };

int	main()
{
	enum builtins str;
	// char	*s;

	str = pwd;
	printf("%d\n", str);
}