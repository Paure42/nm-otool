#include "../includes/u_libft.h"

size_t ft_strlen(const char *s)
{
  size_t i;

  i = 0;
  while (s[i])
    i++;
  return (i);
}

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

char *ft_capitalize(const char *s)
{
  char *ret;
  size_t i;
  size_t j;

  i = 0;
  j = 0;
  if (!(ret = malloc(ft_strlen(s) + 1)))
    return 0;
  while (s[i])
    {
      while (s[i] && ft_isalpha(s[i]) == 0)
        i++;
      char c = s[i];
      if (c > 96 && c < 123) {
          ret[j] = c - 32;
        }
      else {
        ret[j] = c;
      }
      if (s[i])
        i++;
      j++;
    }
  ret[j] = 0;
  return (ret);
}
