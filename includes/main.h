#ifndef MAIN_H_
#define MAIN_H_


/*
 * INCLUDE LIBRARY OF FT_NM
*/

#include "./o_error.h"
#include "./r_elf32.h"
#include "./r_elf64.h"
#include "./o_success.h"
#include "./u_list.h"

/*
 * INCLUDE EXTERN LIBRARY
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <elf.h>

/*
 * FUNCTIONS
*/

int main(int argc, char *argv[]);

#endif // MAIN_H_
