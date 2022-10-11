#include <stdio.h>
#include <stdlib.h>

int main()
{
    int    *p;
  //  int    *s = malloc(4 * sizeof(int));
    p = malloc(4 * sizeof(int));
    p[0] = 4;
    printf("%d\n");
    free(p);
//    printf("%d\n", *p);
}