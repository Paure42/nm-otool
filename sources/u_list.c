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
      size_t nb = 0;
      while (new->name[nb] != 0 && ft_isalpha(new->name[nb]) == 0)
        nb++;
      while (tmp)
        {
          size_t tb = 0;
          while (tmp->name[tb] != 0 && ft_isalpha(tmp->name[tb]) == 0)
            tb++;
          if (ft_strcmp(tmp->name + tb, new->name + nb) > 0)
            {
              if (tmp == *list)
                ft_push_front(list, new);
              else
                ft_lstinsert_before(list, tmp, new);
              return;
            }
          tmp = tmp->next;
        }
      ft_push_back(list, new);
    }
}
