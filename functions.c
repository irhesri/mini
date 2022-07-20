# include "minishell.h"

size_t	my_size(char **arr, char *str, short b)
{
	size_t	size;

	size = 0;
	while (b == 1 && str && str[size])
		size++;
	while (b == 2 && arr && arr[size])
		size++;
	return (size);
}

short	my_strncmp(char *str1, char *str2, size_t n)
{
	if (!str1 || !str2)
		return (1);
	while (--n && *str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	return (1);
}