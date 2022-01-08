#ifndef R_ELF64_H_
#define R_ELF64_H_

/*
  * INCLUDE LIBRARY OF FT_NM
*/

#include "./o_error.h"
#include "./o_success.h"
#include "u_list.h"
#include "u_libft.h"

/*
 * INCLUDE EXTERN LIBRARY
*/

#include <sys/stat.h>
#include <elf.h>

/*
 * FUNCTIONS
*/

int r_elf64(const void *ptr, const char *file);

#endif // R_ELF64_H_
