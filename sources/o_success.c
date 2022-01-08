#include "../includes/o_success.h"

extern t_data **data;

void o_success()
{
  t_data *tmp;

  tmp = *data;
  while (tmp)
  {
    dprintf(1, "%016x %c %s\n", tmp->value, tmp->type, tmp->name);
    tmp = tmp->next;
  }
}
