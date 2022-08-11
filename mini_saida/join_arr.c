#include "../minishell.h"

char    **arr_join(char **arr1, char **arr2)
{
    size_t  len;
    char    **new_arr;
    int     i;
    int     j;

    i = 0;
    j = 0;
    len = my_size(arr1, NULL) + my_size(arr2, NULL);
    new_arr = malloc(sizeof(char *) * (len + 1));
    while (arr1 && arr1[i])
        new_arr[j++] = arr1[i++];
    i = 0;
    while (arr2 && arr2[i])
        new_arr[j++] = arr2[i++];
    new_arr[j] = NULL;
    if (arr1)
        free(arr1);
    if (arr2)
        free(arr2);
    return (new_arr);
}
