#include "../includes/r_elf64.h"
#include <stdio.h>



static inline void s_weak(Elf64_Sym symtab)
{
  if (ELF64_ST_BIND(symtab.st_info == STT_OBJECT))
    {
      if (symtab.st_shndx == SHN_UNDEF)
        {
          printf("v\n");
        } // if a weak undefined sumbol is linked and the symbol is not defined
      else
        {
          printf("V\n");
        } // if a weak defined symbol is linkded with a normal defined symbol
    } // The symbol is associated with a data object
  if (symtab.st_shndx == SHN_UNDEF)
    {
      printf("w\n");
    } // if a weak undefined symbol symbol is linked and the symbol is not defined
  else
    {
      printf("W\n");
    } // if a weak defined symbol is linked with a normal defined symbol
}

void r_elf64(const void *ptr, const char *file)
{
  Elf64_Ehdr *header = (Elf64_Ehdr*)ptr; // header in elf64 of ptr
  Elf64_Shdr *sections = (Elf64_Shdr*)((char*)ptr + header->e_shoff); // locate the section table in the header
  Elf64_Sym *symtab = NULL;
  for (int i = 0; i < header->e_shnum; i++)
    {
      if (sections[i].sh_type == SHT_SYMTAB) {
        symtab = (Elf64_Sym*)((char*)ptr + sections[i].sh_offset);
        break;
      }
    }
  if (symtab == NULL)
    {
      o_error(file, "no symbols");
      return;
    } // if there are no symbols in the table
  printf("there is %ld symbols in the table\n", sizeof(symtab));
  for (size_t i = 0; i < sizeof(symtab); i++)
    {
      if (symtab[i].st_value == SHN_ABS)
        {
          printf("A\n");
        } // he symbol's value is absolute
      else if (symtab[i].st_shndx == SHN_COMMON)
        {
          printf("C\n");
        } // the symbol is common
      else
        {
          switch (ELF64_ST_BIND(symtab[i].st_info)) {
          case STT_NOTYPE : // the symbol's type is not defined
            printf("U\n");
            break;
          case STB_WEAK : // weak  symbols  resemble  global  symbols, but their definitions have lower precedence
            s_weak(symtab[i]);
            break;
          }
        }
    }
}
