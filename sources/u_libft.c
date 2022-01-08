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

int ft_strcmp(const char *s1, const char *s2)
{
  size_t i;

  i = 0;
  while (s1[i] && s2[i]
         && (unsigned char)s1[i] == (unsigned char)s2[i])
    i++;
  return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int ft_isalpha(int c)
{
  if ((c > 64 && c < 91) || (c > 96 && c < 123))
    return (1);
  return (0);
}
