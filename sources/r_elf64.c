#include "../includes/r_elf64.h"
#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

extern t_data **data;

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


static inline void get_symbols_names(const void *ptr, const Elf64_Shdr *section_header, const Elf64_Sym *symtab,
                                     int i, int j, t_data *new)
  {
    char *strtab = (char *)(ptr + section_header[section_header[i].sh_link].sh_offset);
    new->name = ft_strdup(strtab + symtab[j].st_name);
  }

static inline void get_symbols_types(const Elf64_Sym *symtab, int j, t_data *new)
{
  switch (ELF64_ST_TYPE(symtab[j].st_info))
    {
      case STB_WEAK :
        new->type = 'w';
    }
}

static inline int get_symbols_attributes(const void *ptr, const Elf64_Shdr *section_header,
                                         const Elf64_Sym *symtab, int i)
{
  for (size_t j = 0;j < (section_header[i].sh_size / section_header[i].sh_entsize); j++)
  {
    t_data *new;
    if (!(new = malloc(sizeof(t_data))))
      return (-1);
    new->next = NULL;
    new->value = symtab[j].st_value;
    get_symbols_names(ptr, section_header, symtab, i, j, new);
    /* get_symbols_types(symtab, j, new); */
    /* get_symbols_sections(ptr, section_header, symtab, j, i); */
    if (ft_strcmp(new->name, "") != 0)
      ft_push_sort(data, new);
    else {
      free(new->name);
      free(new);
    } // add new to the list if the name of the symbol exists

  }
  return (0);
}

int r_elf64(const void *ptr, const char *file)
{
  if (s_elf64_machine(file, ptr) == -1)
    return (-1);
  if (s_elf64_header_values(file, ptr) == -1)
    return (-1);
  Elf64_Ehdr *header = (Elf64_Ehdr*)ptr; // header of elf64 file
  Elf64_Shdr *section_header = (Elf64_Shdr*)((char*)ptr + header->e_shoff); // locate the section header
  /* Elf64_Phdr *prog_header = ((Elf64_Phdr*)((char*)ptr + header->e_phoff)); // locate the program header */
  for (int i = 0; i < header->e_shnum; i++)
    {
      if (section_header[i].sh_type == SHT_SYMTAB || section_header[i].sh_type == SHT_DYNSYM)
        {
          Elf64_Sym *symtab = NULL;
          symtab = (Elf64_Sym*)((char*)ptr + section_header[i].sh_offset);
          if (get_symbols_attributes(ptr, section_header, symtab, i) == -1)
            return (-1);
        }
    }
  if (!*data)
    {
      o_error(file, "no symbols");
      return(-1);
    } // if there are no symbols in the table
  return (0);
}
