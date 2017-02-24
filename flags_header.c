/*
** flags_header.c for  in /home/jacqui_p/rendu/PSU_2016_nmobjdump/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Thu Feb 23 16:14:46 2017 Pierre-Emmanuel Jacquier
** Last update Fri Feb 24 19:55:12 2017 Pierre-Emmanuel Jacquier
*/

#include "objdump.h"

void bitset_flagheader(int *flags, int type)
{
  if (type == ET_REL)
     *flags |= HAS_RELOC;
   else if (type == ET_DYN)
     *flags |= DYNAMIC;
   else if (type == ET_EXEC)
     *flags |= EXEC_P;
}

void bitset_flagsections(int *flags, int type)
{
  if (type == SHT_SYMTAB || type == SHT_DYNSYM)
      *flags |= HAS_SYMS;
    if (type == SHT_DYNAMIC)
      *flags |= D_PAGED;
}

void print_bitset(int flag)
{
  char *comma = "";
  if (flag & HAS_RELOC)
    {
      PRINTER("HAS_RELOC", comma)
    }
    if (flag & EXEC_P)
    {
      PRINTER("EXEC_P", comma)
    }
  if (flag & HAS_SYMS)
    {
      PRINTER("HAS_SYMS", comma)
    }
  if (flag & DYNAMIC)
    {
      PRINTER("DYNAMIC", comma)
    }
  if (flag & D_PAGED)
    {
      PRINTER("D_PAGED", comma)
    }
  printf("\n");
}

void get_flag_value64(t_data_info *info)
{
  int i;
  int flags;

  flags = 0;
  i = 0;
  bitset_flagheader(&flags, (info->elf64_header)->e_type);
  while (i < info->shnum)
    {
      bitset_flagsections(&flags, (info->shdr64[i]).sh_type);
      i++;
    }
  info->flags = flags;
}

void get_flag_value32(t_data_info *info)
{
  int i;
  int flags;

  flags = 0;
  i = 0;
  bitset_flagheader(&flags, (info->elf32_header)->e_type);
  while (i < info->shnum)
    {
      bitset_flagsections(&flags, (info->shdr32[i]).sh_type);
      i++;
    }
  info->flags = flags;
}
