/*
** objdump.h for  in /home/jacqui_p/rendu/PSU_2016_nmobjdump/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed Feb 22 11:54:09 2017 Pierre-Emmanuel Jacquier
** Last update Thu Feb 23 19:28:49 2017 Pierre-Emmanuel Jacquier
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

#include "flags.h"

typedef struct s_data_info
{
  Elf64_Ehdr	*elf_header;
  Elf64_Shdr	*shdr;
  char				*strtab;
  int					flags;
  int					shnum;

}              t_data_info;

#define PRINTER(x, comma) printf("%s%s", comma, x); comma = ", ";

int what_architecture(void *data, size_t datasize);
void print_sh_name64(Elf64_Shdr *shdr, char *strtab, int shnum);
void print_sh_name32(Elf32_Shdr *shdr, char *strtab, int shnum);
int iself_file(void *data, size_t datasize);
void print_bitset(int flag);
void get_flag_value(t_data_info *info);
void print_all_section(t_data_info *info);

#endif /* !OBJDUBP_H_ */
