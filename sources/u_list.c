#include "../includes/u_list.h"

void ft_push_back(t_data **list, t_data *new)
{
  t_data *tmp;

  if (!list || !new)
    return;
  new->next = 0;
  if (!*list)
    {
      *list = new;
      return;
    }
  tmp = *list;
  while (tmp->next)
    tmp = tmp->next;
  tmp->next = new;
}

void ft_push_front(t_data **list, t_data *new)
{
  if (!list || !new)
    return;
  new->next = *list;
  *list = new;
}

void ft_lstclear(t_data **list)
{
  t_data *tmp;

  if (!list)
    return;
  while (*list)
    {
      tmp = *list;
      *list = tmp->next;
      free(tmp->name);
      free(tmp);
    }
}

int ft_lstsize(t_data **list)
{
  int    n;
  t_data *tmp;

  n = 0;
  if (!list)
    return (0);
  tmp = *list;
  while (tmp)
    {
      tmp = tmp->next;
      n++;
    }
  return (n);
}
