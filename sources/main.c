#include "../includes/main.h"
#include <strings.h>

// TODO REPLACE STRLEN WITH CUSTOM STRLEN

/*
  * GLOBALE VARIABLES
*/
 int g_buf_size;
 char *g_buffer;

static inline int m_check_elf(const char *file, const char *ptr)
{
  switch ((unsigned char)ptr[EI_DATA]) {
  case ELFDATA2LSB :
    break;
  case  ELFDATA2MSB :
    break;
  default :
    o_error(file, "Incorrect elf data encoding");
    return (-1);
  } // check for data encoding, ie littlen endian or big endian

  switch((unsigned char)ptr[EI_VERSION]) {
  case  EV_CURRENT :
    break;
  default :
    o_error(file, "Incorrect elf verion");
    return (-1);
  } // check for elf version

  switch ((unsigned char)ptr[EI_OSABI]) {
    case ELFOSABI_SYSV :
      break;
    case ELFOSABI_HPUX :
      break;
    case ELFOSABI_NETBSD :
      break;
    case ELFOSABI_SOLARIS :
      break;
    case ELFOSABI_IRIX :
      break;
    case ELFOSABI_FREEBSD :
      break;
    case ELFOSABI_TRU64 :
      break;
    case ELFOSABI_ARM :
      break;
    case ELFOSABI_STANDALONE :
      break;
    default :
      o_error(file, "Incore elf ABI");
  } // check for elf ABI
  switch(((Elf64_Ehdr*)ptr)->e_type) {
    case ET_REL :
      break;
    case ET_EXEC :
      break;
    case ET_DYN :
      break;
    case ET_CORE :
      break;
  default :
    o_error(file, "Incorrect elf type");
    return (-1);
  } // check for elf type
  return (0);
}

static inline void m_read_file(const char *file, const char *ptr, const struct stat *statbuf)
{
  if ((unsigned char)ptr[EI_MAG0] == 0x7f &&
      (unsigned char)ptr[EI_MAG1] == 'E' &&
	  (unsigned char)ptr[EI_MAG2] == 'L' &&
	  (unsigned char)ptr[EI_MAG3] == 'F') {
	// if the file is an elf
	if (m_check_elf(file, ptr) == -1)
    return;
	bzero(g_buffer, g_buf_size); // TODO REPLACE WITH CUSTOM BZERO
	switch ((unsigned char)ptr[EI_CLASS]) {
	case ELFCLASS64: // if elf is 64 bits
	  r_elf64(ptr, file);
	  break;
	case ELFCLASS32: // if elf is 32 bits
	  r_elf32(ptr);
	  break;
  default:
    o_error(file, "Incorrect elf type");
    break;
	}
  }
  (void)statbuf;
}

static inline int m_open(const char *file) {
  int fd;
  char *ptr;
  struct stat statbuf;

  if ((fd = open(file, O_RDONLY)) < 0) {
    o_error(file, "No such file");
    return (EXIT_FAILURE);
  } // if open failed
  if (fstat(fd, &statbuf) < 0) {
    o_error(file, "Cannot read stat");
    return (EXIT_FAILURE);
  } // if fstat failed
  else if (S_ISREG(statbuf.st_mode) == false) {
    o_error(file, "Incorrect file type");
    return (EXIT_FAILURE);
  } // check if file is a regular file
  ptr = mmap(NULL, statbuf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (ptr == MAP_FAILED) {
    o_error(file, "Mapping Failed\n");
    return (EXIT_FAILURE);
  } // if mapping failed

  m_read_file(file, ptr, &statbuf);
  munmap((void *)ptr, statbuf.st_size);
  close(fd);
  return (0);
}

int main(int argc, char *argv[])
{
  g_buffer = NULL;
  g_buf_size = 4096;

  if ((g_buffer = malloc(g_buf_size * sizeof(char))) == 0)
    {
      return(EXIT_FAILURE);
    } // allocate the buffer for the output
  if (argc < 2)
    {
      m_open("a.out");
      o_success();
    } // if there is no arguments, tries to open a.out by default.
  else
    {
      for (int i = 1; i < argc; i++) {
        m_open(argv[i]);
        o_success();
      }
    } // loop through all files in arg$
  free(g_buffer);
  return (EXIT_SUCCESS);
}
