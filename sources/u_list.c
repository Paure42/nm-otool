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

void ft_lstinsert_before(t_data **list, t_data *link, t_data *new)
{
  t_data *tmp;

  tmp = *list;
  while (tmp && tmp->next != link)
    tmp = tmp->next;
  new->next = tmp->next;
  tmp->next = new;
}
#include <stdio.h>
void ft_push_sort(t_data **list, t_data *new)
{
  t_data *tmp;
  if (!list || !new)
    return;
  tmp = *list;
  if (!tmp)
    {
      *list = new;
    }
  else
    {
      char *new_cap = ft_capitalize(new->name);
      while (tmp)
        {
          char *tmp_cap = ft_capitalize(tmp->name);
          if (ft_strcmp(tmp_cap, new_cap) > 0)
            {
              if (tmp == *list)
                ft_push_front(list, new);
              else
                {
                  ft_lstinsert_before(list, tmp, new);
                }
              free(tmp_cap);
              free(new_cap);
              return;
            }
          free(tmp_cap);
          tmp = tmp->next;
        }
      free(new_cap);
      ft_push_back(list, new);
    }
}
