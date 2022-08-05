#include <stdio.h>
#include <stdlib.h>


int	main()
{
	char *str;

	str = malloc(10);
	my_free((void **)(&str));
	printf("%s\n", str);
}