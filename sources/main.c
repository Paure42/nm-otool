#include "../includes/main.h"
#include <elf.h>
#include <stdio.h>
#include <strings.h>

int g_buf_size = 100;
char *g_buffer = NULL;

void m_read_file(const char *file, const char *ptr, const struct stat *statbuf)
{
  if ((unsigned char)ptr[EI_MAG0] == 0x7f &&
      (unsigned char)ptr[EI_MAG1] == 'E' &&
	  (unsigned char)ptr[EI_MAG2] == 'L' &&
	  (unsigned char)ptr[EI_MAG3] == 'F') {
	// if the file is an elf
	bzero(g_buffer, g_buf_size); // TODO REPLACE WITH CUSTOM BZERO
	switch ((unsigned char)ptr[EI_CLASS]) {
	case ELFCLASS64: // if elf is 64 bits
	  r_elf64(ptr, file);
	  break;
	case ELFCLASS32: // if elf is 32 bits
	  r_elf32(ptr);
	  break;
	case ELFCLASSNONE: // error ?
	  o_error(file, "Incorrect elf type");
	  break;
	}
  }
  (void)statbuf;
}

int m_open(const char *file) {
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
	if (argc < 2)
	{
		m_open("a.out");
	} // if there is no arguments, tries to open a.out by default.
	else
	{
    if ((g_buffer = malloc(g_buf_size * sizeof(char))) == 0)
    {
      return(EXIT_FAILURE);
    } // allocate the buffer for the output
		for (int i = 1; i < argc; i++) {
			m_open(argv[i]);
		}
	} // loop through all files in argv
	return (EXIT_SUCCESS);
}
