#ifndef R_ELF64_H_
#define R_ELF64_H_

#include <sys/stat.h>
#include <elf.h>

void r_elf64(void *ptr, struct stat *statbuf);

#endif // R_ELF64_H_
