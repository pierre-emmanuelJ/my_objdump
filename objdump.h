/*
** objdump.h for  in /home/jacqui_p/rendu/PSU_2016_nmobjdump/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed Feb 22 11:54:09 2017 Pierre-Emmanuel Jacquier
** Last update Sat Feb 25 17:54:05 2017 Pierre-Emmanuel Jacquier
*/

#ifndef OBJDUBP_H_
# define OBJDUBP_H_

#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "flags.h"

typedef struct s_data_info
{
  Elf64_Ehdr  *elf64_header;
  Elf64_Shdr  *shdr64;
  Elf32_Ehdr  *elf32_header;
  Elf32_Shdr  *shdr32;
  char        *strtab;
  char        *file_path;
  int         flags;
  int         shnum;
}              t_data_info;

typedef struct s_section_printer
{
  unsigned long int  sh_addr;
  unsigned long      sh_size;
  char               *section;
  int                addr_format;
}              t_section_printer;


#define PRINTER(x, comma) printf("%s%s", comma, x); comma = ", ";

int what_architecture(void *data, size_t datasize);
void print_sh_name64(Elf64_Shdr *shdr, char *strtab, int shnum);
void print_sh_name32(Elf32_Shdr *shdr, char *strtab, int shnum);
int iself_file(void *data, size_t datasize);
void print_bitset(int flag);
void get_flag_value64(t_data_info *info);
void get_flag_value32(t_data_info *info);
void print_all_section64(t_data_info *info);
void print_all_section32(t_data_info *info);
int is_regular_file(const char *path);

#endif /* !OBJDUBP_H_ */
