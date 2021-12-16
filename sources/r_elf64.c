#include "../includes/r_elf64.h"
#include <elf.h>
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

static inline void get_symbols_values(const Elf64_Sym *symtab, int j)
  {
    Elf64_Addr value = symtab[j].st_value;
    snprintf((g_buffer + strlen(g_buffer)), (g_buf_size - strlen(g_buffer)), "value : %ld ", value);
  }

static inline void get_symbols_names(const void *ptr, const Elf64_Shdr *section_header, const Elf64_Sym *symtab, int i, int j)
  {
    char *strtab = (char *)(ptr + section_header[section_header[i].sh_link].sh_offset);
    snprintf((g_buffer + strlen(g_buffer)), (g_buf_size - strlen(g_buffer)), "name : %s\n", strtab + symtab[j].st_name);
  }

static inline void get_symbols_sections(const void *ptr, const Elf64_Shdr *section_header, const Elf64_Sym *symtab, int j, int i)
{
  char *strtab= (char *)(ptr + section_header[section_header[i].sh_link].sh_offset);
  printf("SECTION HEADER NAME : %s\n", strtab + section_header[symtab[j].st_shndx].sh_name);
}

static inline void get_symbols_attributes(const void *ptr, const Elf64_Shdr *section_header, const Elf64_Sym *symtab, int i)
{
  for (size_t j = 0; j < (section_header[i].sh_size/section_header[i].sh_entsize); j++)
    {
      if (symtab[j].st_size > 0)
      {
        get_symbols_values(symtab, j);
        get_symbols_names(ptr, section_header, symtab, i, j);
        /* get_symbols_sections(ptr, section_header, symtab, j, i); */
      }
    }
}
void r_elf64(const void *ptr, const char *file)
{
  if (s_elf64_machine(file, ptr) == -1)
    return;
  if (s_elf64_header_values(file, ptr) == -1)
    return;
  Elf64_Ehdr *header = (Elf64_Ehdr*)ptr; // header of elf64 file
  Elf64_Shdr *section_header = (Elf64_Shdr*)((char*)ptr + header->e_shoff); // locate the section header
  /* Elf64_Phdr *prog_header = ((Elf64_Phdr*)((char*)ptr + header->e_phoff)); // locate the program header */
  for (int i = 0; i < header->e_shnum; i++)
    {
      if (section_header[i].sh_type == SHT_SYMTAB)
        {
          Elf64_Sym *symtab = NULL;
          symtab = (Elf64_Sym*)((char*)ptr + section_header[i].sh_offset); // locate the symbols table in the sections
          get_symbols_attributes(ptr, section_header, symtab, i);
        }
      else if (section_header[i].sh_type == SHT_DYNSYM)
        {
          Elf64_Sym *symtab = NULL;
          symtab = (Elf64_Sym*)((char*)ptr + section_header[i].sh_offset); // locate the symbols table in the sections
          get_symbols_attributes(ptr, section_header, symtab, i);
        }
      else if (section_header[i].sh_type == SHT_HASH)
        {
          Elf64_Sym *symtab = NULL;
          symtab = (Elf64_Sym*)((char*)ptr + section_header[i].sh_offset); // locate the symbols table in the sections
          get_symbols_attributes(ptr, section_header, symtab, i);
        }
    } // TODO sanity checking to make sure that none of the
      // indexes are out of range for the section they are
      // indexing into, and that sh_entsize and and e_shentsize
      // match the sizeof the structs you are using, just in case the ELF file has been corrupted
  if (strlen(g_buffer) == 0)
    {
      snprintf(g_buffer, g_buf_size, "%s : no symbols", file);
      return;
    } // if there are no symbols in the table
}
