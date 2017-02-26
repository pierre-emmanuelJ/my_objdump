/*
** print_sections32.c for  in /home/jacqui_p/rendu/PSU_2016_nmobjdump/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Sun Feb 26 12:12:38 2017 Pierre-Emmanuel Jacquier
** Last update Sun Feb 26 12:25:37 2017 Pierre-Emmanuel Jacquier
*/

#include "objdump.h"

static int is_section_to_print32(t_data_info *info, int i, int type)
{
  char *tmp;

  tmp = info->strtab;
  return (!(type == SHT_NULL || info->shdr32[i].sh_size == 0 ||
     type == SHT_SYMTAB || type == SHT_NOBITS ||
     ((info->flags & HAS_RELOC) && (type == SHT_RELA || type == SHT_REL)) ||
     strcmp(&tmp[info->shdr32[i].sh_name], ".shstrtab") == 0 ||
     strcmp(&tmp[info->shdr32[i].sh_name], ".strtab") == 0 ||
     strcmp(&tmp[info->shdr32[i].sh_name], ".symtab") == 0));
}

static void print_section32(char *section, t_data_info *info, int pos)
{
	t_section_printer print;
	unsigned long i;

	i = 0;
	print.sh_addr = info->shdr32[pos].sh_addr;
  print.sh_size = info->shdr32[pos].sh_size;
	print.section = section;
	printf("Contents of section %s:\n", &info->strtab[info->shdr32[pos].sh_name]);
  print.addr_format = sh_addr_format(print.sh_addr, print.sh_size);
	while (i < print.sh_size)
    {
		  printf(" %0*lx ", print.addr_format, print.sh_addr);
		  print_line(&print, &i);
		  print.sh_addr += 16;
		  printf("\n");
    }
}

void print_all_section32(t_data_info *info)
{
  int i;
	char *section;

  i = 0;
	section = (char*)info->elf32_header;
  while (i < info->shnum)
    {
      section += info->shdr32[i].sh_offset;
		  if (is_section_to_print32(info, i, info->shdr32[i].sh_type))
			  print_section32(section, info, i);
		  section = (char *)info->elf32_header;
		  i++;
		}
}
