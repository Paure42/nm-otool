#ifndef R_ELF64_H_
#define R_ELF64_H_

/*
  * Include library of ft_nm
*/

#include "./o_error.h"

/*
 * Include extern library
*/

#include <sys/stat.h>
#include <elf.h>

void r_elf64(const void *ptr, const char *file);

#endif // R_ELF64_H_
