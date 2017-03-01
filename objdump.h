/*
** objdump.h for  in /home/jacqui_p/rendu/PSU_2016_nmobjdump/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed Feb 22 11:54:09 2017 Pierre-Emmanuel Jacquier
** Last update Sun Feb 26 13:16:44 2017 Pierre-Emmanuel Jacquier
*/

#ifndef OBJDUMP_H_
# define OBJDUMP_H_

# include <elf.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <unistd.h>
# include <string.h>
# include <ctype.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "flags.h"

/*
** yan typedef Elf64_Ehdr
*/

/*
** yan typedef Elf64_Shdr
*/

/*
** yan typedef Elf32_Ehdr
*/

/*
** yan typedef Elf32_Shdr
*/

# define PRINTER(x, comma) printf("%s%s", comma, x); comma = ", "

typedef struct  s_data_info
{
  Elf64_Ehdr    *elf64_header;
  Elf64_Shdr    *shdr64;
  Elf32_Ehdr    *elf32_header;
  Elf32_Shdr    *shdr32;
  char          *strtab;
  char          *file_path;
  int           flags;
  int           shnum;
}               t_data_info;

typedef struct  s_section_printer
{
  unsigned long sh_addr;
  unsigned long sh_size;
  char          *section;
  int           addr_format;
  char          str[32];
}               t_section_printer;

void    get_flag_value64(t_data_info *info);
void    print_bitset(int flag);
void    get_flag_value32(t_data_info *info);
void    print_all_section64(t_data_info *info);
void    print_all_section32(t_data_info *info);
void    print_line(t_section_printer *print, unsigned long *pos);
int     what_architecture(void *data, size_t datasize);
int     iself_file(void *data, size_t datasize);
int     is_regular_file(const char *path);
int     is_empty_file(const char *path);
int     sh_addr_format(unsigned long addr, int size);
int     open_file(char *path, int *fd, char *file);
int     filesize(int fd);

#endif /* !OBJDUMP_H_ */
