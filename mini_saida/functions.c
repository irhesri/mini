#include "h.h"

// returns arr size if str NULL
// returns str size if arr NULL
// returns 0 if both of them NULL
// returns str size + arr size if both of them !NULL
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

// returns substring of str from the beginning to char c 
// c not included
// returns copy of str if c doesn't exist
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

//	returns c index in str
//	returns -1 if c doesn't exist
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

// b == 1 : free(str1)
// b == 2 : free(str2)
// b == 3 : free both
char	*free_join(char *str1, char *str2, short b)
{
	char	*str;

	if (!str2)
		return (str1);
	if (!str1)
		return (str2);
	str = ft_strjoin(str1, str2);
	if (!b || b == 1)
		free (str1);
	if (!b || b == 2)
		free (str2);
	return (str);
}

// b == 0 add str in the beginning of arr
// b == -1 add str in the end of arr
// i free arr
char	**array_realloc(char **arr, char *str, short b)
{
	char	**res;
	size_t	size;
	int		i;
	int		j;

	if (!str)
		return (arr);
	size = my_size(arr, NULL) + 1;
	res = malloc(sizeof(char *) * (size + 1));
	i = b;
	j = -1;
	while (arr && arr[++j])
		res[++i] = arr[j];
	i += (b == -1);
	res[i * (b != 0) + b * (b == 0)] = str;
	res[++i] = NULL;
	if (arr)
		free (arr);
	return (res);
}

short	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

short	is_alphabet(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

// char	**array_join(char **arr1, char **arr2, short b)
// {

// }
