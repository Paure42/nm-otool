#ifndef R_ELF32_H_
#define R_ELF32_H_

#include <sys/stat.h>
#include <elf.h>

void r_elf32(const void *ptr, const struct stat *statbuf);

#endif // R_ELF32_H_
