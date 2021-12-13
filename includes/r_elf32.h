#ifndef R_ELF32_H_
#define R_ELF32_H_

#include <sys/stat.h>
#include <elf.h>

void r_elf32(void *ptr, struct stat *statbuf);

#endif // R_ELF32_H_
