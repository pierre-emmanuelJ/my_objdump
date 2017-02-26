/*
** elf_check.c for  in /home/jacqui_p/rendu/PSU_2016_nmobjdump/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Thu Feb 23 16:10:01 2017 Pierre-Emmanuel Jacquier
** Last update Thu Feb 23 16:14:19 2017 Pierre-Emmanuel Jacquier
*/

#include "objdump.h"

int     iself_file(void *data, size_t datasize)
{
  char  *file;

  if (datasize < 4)
    return (0);
  file = (char *)data;
  if (*file != ELFMAG0)
    return (0);
  file++;
  if (*file != ELFMAG1)
    return (0);
  file++;
  if (*file != ELFMAG2)
    return (0);
  file++;
  if (*file != ELFMAG3)
    return (0);
  return (1);
}
