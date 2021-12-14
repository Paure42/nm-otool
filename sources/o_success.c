#include "../includes/o_success.h"

extern int  g_buf_size;
extern char *g_buffer;

void o_success()
{
  write(1, g_buffer, g_buf_size);
}
