#include "../includes/u_libft.h"

char *ft_strdup(const char *s1)
{
  int   i;
  char  *dest;

  i = 0;
  dest = 0;
  while (s1[i] != 0)
    i++;
  if (!(dest = malloc((i + 1) * sizeof(char))))
    return (0);
  i = 0;
  while (s1[i])
    {
      dest[i] = s1[i];
      i++;
    }
  dest[i] = 0;
  return (dest);
}
