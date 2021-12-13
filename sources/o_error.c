#include "../includes/o_error.h"

void o_error(const char *object, const char *reason)
{
    dprintf(2, "ft_nm: '%s' : %s\n",  object, reason);
}
