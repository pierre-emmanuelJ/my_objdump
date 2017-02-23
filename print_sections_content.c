/*
** print_sections_content.c for  in /home/jacqui_p/rendu/PSU_2016_nmobjdump/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Thu Feb 23 16:32:46 2017 Pierre-Emmanuel Jacquier
** Last update Thu Feb 23 19:32:02 2017 Pierre-Emmanuel Jacquier
*/

#include "objdump.h"

static int is_section_to_print(t_data_info *info, int i, int type)
{
  char *tmp;

  tmp = info->strtab;
  return !(type == SHT_NULL || info->shdr[i].sh_size == 0 ||
     type == SHT_SYMTAB || type == SHT_NOBITS ||
     ((info->flags & HAS_RELOC) && (type == SHT_RELA || type == SHT_REL)) ||
     strcmp(&tmp[info->shdr[i].sh_name], ".shstrtab") == 0 ||
     strcmp(&tmp[info->shdr[i].sh_name], ".strtab") == 0 ||
     strcmp(&tmp[info->shdr[i].sh_name], ".symtab") == 0);
}

void print_section(char  *section, char *next)
{
	int line;

	line = 0;
	while(section <= next)
	  {
		  printf("%p ", section);
		  while (line < 16)
			  {
			  line++;
			  }
		  printf("\n");
		  section++;
	  }
}

void print_all_section(t_data_info *info)
{
  int i;
	char *section;
	char *next;

  i = 0;
	next = (char*)info->elf_header;
  while (i < info->shnum)
    {
		  section = (char *)(&info->shdr[i]);
		  next += info->shdr[i].sh_offset;
		  if (is_section_to_print(info, i, info->shdr[i].sh_type))
			{
			  print_section(section, next);
			}
		  next = (char *)info->elf_header;
		  i++;
		}
}
