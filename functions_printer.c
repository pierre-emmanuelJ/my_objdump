/*
** functions_printer.c for  in /home/jacqui_p/rendu/PSU_2016_nmobjdump/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Sun Feb 26 12:16:37 2017 Pierre-Emmanuel Jacquier
** Last update Sun Feb 26 13:19:42 2017 Pierre-Emmanuel Jacquier
*/

#include "objdump.h"

int     sh_addr_format(unsigned long addr, int size)
{
  int   i;
  int   length;

  i = 0;
  length = addr + size;
  while (length > 0)
    {
      length = length / 16;
      i++;
    }
  length = length % 16;
  if (i > 6)
    return (6);
  if (i > 4)
    return (i);
  return (4);
}

static void     print_str(t_section_printer *print)
{
  int           i;

  i = 0;
  printf(" ");
  while (i < 16)
    {
      if (isprint(print->str[i]))
        printf("%c", print->str[i]);
      else
        printf(".");
      i++;
    }
}

static void     print_section_line(unsigned long *pos,
                                   int *strpos,
                                   t_section_printer *print)
{
  int           j;

  j = 0;
  while (j < 4)
    {
      if (*pos < print->sh_size)
        {
          printf("%02x", *print->section & 0xff);
          print->str[*strpos] = *print->section;
          print->section++;
          (*strpos)++;
        }
      else
        {
          printf("  ");
          print->str[*strpos] = ' ';
          (*strpos)++;
        }
      (*pos)++;
      j++;
    }
}

void    print_line(t_section_printer *print, unsigned long *pos)
{
  int   i;
  int   strpos;

  i = 0;
  strpos = 0;
  while (i < 4)
    {
      print_section_line(pos, &strpos, print);
      printf(" ");
      i++;
    }
  print_str(print);
}
