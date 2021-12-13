#include "../includes/r_elf64.h"
#include <stdio.h>

static inline void test_header_type(uint32_t type, uint32_t value, char *name)
{
  if (type == value) {
    printf("%s\n", name);
  }
}

void r_elf64(const void *ptr)
{
  Elf64_Ehdr *eh = (Elf64_Ehdr*)ptr; // header in elf64 of ptr
  for (int i = 0; i < eh->e_phnum; i++)
    {
      Elf64_Phdr *ph = (Elf64_Phdr *)((char *)ptr +
                                      (eh->e_phoff + eh->e_phentsize * i));
      /* uint32_t type = ph->p_type; */
      if (ph->p_type == PT_DYNAMIC)
        {
          const Elf64_Dyn *dtag_table = (const Elf64_Dyn*)(ptr + ph->p_offset); // table of dtag in the segment
          const char *strtab = NULL;
          int j = 0;
          while (1)
            {
              if (dtag_table[j].d_tag == DT_NULL)
                {
                  break;
                } // the end of the table is marked with DT_NULL
              if (dtag_table[j].d_tag == DT_STRTAB)
                {
                  strtab = (const char*)dtag_table[j].d_un.d_ptr;
                  break;
                }
              j++;
            } // looking for the string table
          if (strtab == NULL)
            {
              break;
            } // if there is no string in table
          j = 0;
          while (1)
            {
              if (dtag_table[j].d_tag == DT_NULL)
                {
                  break;
                } // end of table is marked with DT_NULL
              if (dtag_table[j].d_tag == DT_NEEDED)
                {
                  printf("shared lib: %s\n%ld\n", &strtab[dtag_table[j].d_un.d_val], dtag_table[j].d_un.d_val);
                }
              j++;
            } // looking for shared library names inside the string table
        } // find PT_DYNAMIC segment and read it's data


      /* test_header_type(type, PT_NULL, "PT_NULL"); */
      /* test_header_type(type, PT_LOAD, "PT_LOAD"); */
      /* test_header_type(type, PT_DYNAMIC, "PT_DYNAMIC"); */
      /* test_header_type(type, PT_INTERP, "PT_INTERP"); */
      /* test_header_type(type, PT_NOTE, "PT_NOTE"); */
      /* test_header_type(type, PT_SHLIB, "PT_SHLIB"); */
      /* test_header_type(type, PT_PHDR, "PT_PHDR"); */
      /* test_header_type(type, PT_TLS, "PT_TLS"); */
      /* test_header_type(type, PT_NUM, "PT_NUM"); */
      /* test_header_type(type, PT_LOOS, "PT_LOOS"); */
      /* test_header_type(type, PT_GNU_EH_FRAME, "PT_GNU_EH_FRAME"); */
      /* test_header_type(type, PT_GNU_STACK, "PT_GNU_STACK"); */
      /* test_header_type(type, PT_GNU_RELRO, "PT_GNU_RELRO"); */
      /* test_header_type(type, PT_LOSUNW, "PT_LOSUNW"); */
      /* test_header_type(type, PT_SUNWBSS, "PT_SUNWBSS"); */
      /* test_header_type(type, PT_SUNWSTACK, "PT_SUNWSTACK"); */
      /* test_header_type(type, PT_HISUNW, "PT_HISUNW"); */
      /* test_header_type(type, PT_HIOS, "PT_HIOS"); */
      /* test_header_type(type, PT_LOPROC, "PT_LOPROC"); */
      /* test_header_type(type, PT_HIPROC, "PT_HIPROC"); */
    }
}
