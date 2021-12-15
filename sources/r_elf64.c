#include "../includes/r_elf64.h"
#include <stdio.h>
#include <string.h>

extern int  g_buf_size;
extern char *g_buffer;

static inline int s_elf64_machine(const char *file, const void *ptr)
{
  switch(((Elf64_Ehdr*)ptr)->e_machine) {
  case EM_M32 :
    break;
  case EM_SPARC :
    break;
  case EM_386 :
    break;
  case EM_68K :
    break;
  case EM_88K :
    break;
  case EM_860 :
    break;
  case EM_MIPS :
    break;
  case EM_PARISC :
    break;
  case EM_SPARC32PLUS :
    break;
  case  EM_PPC :
    break;
  case EM_PPC64 :
    break;
  case EM_S390 :
    break;
  case EM_ARM :
    break;
  case EM_SH :
    break;
  case EM_SPARCV9 :
    break;
  case EM_IA_64 :
    break;
  case EM_X86_64 :
    break;
  default :
         o_error(file, "Incorrect elf machine");
         return (-1);
    }
  return (0);
}

static inline int s_elf64_header_values(const char *file, const void *ptr)
{
  switch (((Elf64_Ehdr*)ptr)->e_shnum) {
    case SHN_LORESERVE :
      o_error(file, "Incorrect entries number in the section header table");
      return(-1);
    case 0 :
      o_error(file, "Incorrect entries number in the section header table");
      return(-1);
  }
  return (0);
}

static inline void get_symbols_values(const Elf64_Sym *symtab, int i)
  {
    Elf64_Addr value = symtab[i].st_value;
    snprintf((g_buffer + strlen(g_buffer)), (g_buf_size - strlen(g_buffer)), "value : %ld ", value);
  }

static inline void get_symbols_names(const void *ptr, const Elf64_Shdr *sections, const Elf64_Sym *symtab, int i) // get symbols names
{
  char *strtab= (char *)(ptr + sections[sections[i].sh_link].sh_offset);
  for (size_t j = 0; j < (sections[i].sh_size/sections[i].sh_entsize); j++)
    {
      snprintf((g_buffer + strlen(g_buffer)), (g_buf_size - strlen(g_buffer)), "name : %s\n", strtab + symtab[j].st_name);
    }
}

void r_elf64(const void *ptr, const char *file)
{
  if (s_elf64_machine(file, ptr) == -1)
    return;
  if (s_elf64_header_values(file, ptr) == -1)
    return;
  Elf64_Ehdr *header = (Elf64_Ehdr*)ptr; // header in elf64 of ptr
  Elf64_Shdr *sections = (Elf64_Shdr*)((char*)ptr + header->e_shoff); // locate the section table in the header
  Elf64_Sym *symtab = NULL;
  for (int i = 0; i < header->e_shnum; i++)
    {
      if (sections[i].sh_type == SHT_SYMTAB)
        {
          symtab = (Elf64_Sym*)((char*)ptr + sections[i].sh_offset); // locate the symbols table in the sections
          printf("SH_SIZE : %ld\nSH_ENTSIZE : %ld\nE_SHENTSIZE : %d\n", sections[i].sh_size, sections[i].sh_entsize, header->e_shentsize);
          if (sections[i].sh_entsize == header->e_shentsize)
            {
              get_symbols_values(symtab, i);
              get_symbols_names(ptr, sections, symtab, i);
              break;
            }
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
