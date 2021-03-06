#ifndef U_LIST_H_
#define U_LIST_H_

/*
 * STRUCTURE TO STOCK THE DATA
*/

typedef struct s_data {
  unsigned int  value;
  char          *name;
  char          type;
  struct s_data *next;
} t_data;

/*
 * INCLUDE LIBRARY OF FT_NM
*/

#include "u_libft.h"

/*
 * INCLUDE EXTERN LIBRARY
*/

#include <stdlib.h>

/*
 * FUNCTIONS
*/

void ft_push_back(t_data **list, t_data *new);
void ft_push_front(t_data **list, t_data *new);
void ft_lstclear(t_data **list);
int ft_lstsize(t_data **list);
void ft_lstinsert_before(t_data **list, t_data *link, t_data *new);
void ft_push_sort(t_data **list, t_data *new);

#endif // U_LIST_H_
