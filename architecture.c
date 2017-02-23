/*
** architecture.c for  in /home/jacqui_p/rendu/PSU_2016_nmobjdump/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Thu Feb 23 16:09:10 2017 Pierre-Emmanuel Jacquier
** Last update Thu Feb 23 16:14:23 2017 Pierre-Emmanuel Jacquier
*/

#include "objdump.h"

int what_architecture(void *data, size_t datasize)
{
  char *file;

  if (datasize < 5)
    return (ELFCLASSNONE);
  file = (char *)data;
  if (file[4] == ELFCLASS32)
    return (ELFCLASS32);
  if (file[4] == ELFCLASS64)
    return (ELFCLASS64);
  return (ELFCLASSNONE);
}

void print_sh_name64(Elf64_Shdr *shdr, char *strtab, int shnum)
{
  int i;

  i = 0;
  while (i < shnum)
    {
      printf("%02d: %s\n", i, &strtab[shdr[i].sh_name]);
      i++;
    }
}

void print_sh_name32(Elf32_Shdr *shdr, char *strtab, int shnum)
{
  int i;

  i = 0;
  while (i < shnum)
    {
      printf("%02d: %s\n", i, &strtab[shdr[i].sh_name]);
      i++;
    }
}
