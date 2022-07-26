#include "minishell.h"

size_t	my_size(char **arr, char *str)
{
	size_t	size;

	size = 0;
	while (str && str[size])
		size++;
	while (arr && arr[size])
		size++;
	return (size);
}

int	my_strncmp(char *str1, char *str2, size_t n)
{
	if (!str1 || !str2)
		return (1);
	while (--n && *str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

char	*my_strdup(char *str, char c)
{
	int		i;
	int		size;
	char	*new;

	size = -1;
	if (c != '\0')
		size = my_search(str, c);
	if (size == -1)
		size = my_size(NULL, str);
	new = malloc(size + 1);
	i = -1;
	while (str[++i] && str[i] != c)
		new[i] = str[i];
	new[i] = '\0';
	return (new);
}

int	my_search(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] != c)
		return (-1);
	return (i);
}

char	*my_strjoin(char *str1, char *str2)
{
	int		i;
	char	*res;

	i = -1;
	res = malloc(my_size(NULL, str1) + my_size(NULL, str2) + 1);
	if (!res)
		exit(printf("allocation error\n"));
	while (*str1)
		res[++i] = *str1++;
	while (*str2)
		res[++i] = *str2++;
	res[++i] = '\0';
	return (res);
}
