#include "../includes/r_elf64.h"
#include <stdio.h>
#include <string.h>

extern int  g_buf_size;
extern char *g_buffer;

static inline void get_names(const void *ptr, const Elf64_Shdr *sections, const Elf64_Sym *symtab, int i) // get symbols names
{
  char *strtab= (char *)(ptr + sections[sections[i].sh_link].sh_offset);
  for (size_t j = 0; j < (sections[i].sh_size/sections[i].sh_entsize); j++)
    {
      snprintf((g_buffer + strlen(g_buffer)), (g_buf_size - strlen(g_buffer)), "name : %s\n", strtab + symtab[j].st_name);
    }
}

void r_elf64(const void *ptr, const char *file)
{
  Elf64_Ehdr *header = (Elf64_Ehdr*)ptr; // header in elf64 of ptr
  Elf64_Shdr *sections = (Elf64_Shdr*)((char*)ptr + header->e_shoff); // locate the section table in the header
  Elf64_Sym *symtab = NULL;
  for (int i = 0; i < header->e_shnum; i++)
    {
      if (sections[i].sh_type == SHT_SYMTAB)
        {
          symtab = (Elf64_Sym*)((char*)ptr + sections[i].sh_offset); // locate the symbols table in the sections
          get_names(ptr, sections, symtab, i);
          break;
        }
    } // TODO sanity checking to make sure that none of the
      // indexes are out of range for the section they are
      // indexing into, and that sh_entsize and and e_shentsize
      // match the sizeof the structs you are using, just in case the ELF file has been corrupted
  if (symtab == NULL)
    {
      snprintf(g_buffer, g_buf_size, "%s : no symbols", file);
      return;
    } // if there are no symbols in the table
  printf("there is %ld symbols in the table\n", sizeof(symtab));
}
