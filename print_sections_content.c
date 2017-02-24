/*
** print_sections_content.c for  in /home/jacqui_p/rendu/PSU_2016_nmobjdump/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Thu Feb 23 16:32:46 2017 Pierre-Emmanuel Jacquier
** Last update Fri Feb 24 19:27:26 2017 Pierre-Emmanuel Jacquier
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


int sh_addr_format(unsigned addr, int size)
{
  int i;
	int length;

	i = 0;
	length = addr + size;
	while (length > 0)
	  {
      length = length / 16;
		  i++;
		}
		if (i > 4)
		  return (i);
		return (4);
}

void print_str(char *str)
{
  int i;

	i = 0;
  printf(" ");
	while (i < 16)
    {
      if (isprint(str[i]))
        printf("%c", str[i]);
      else
        printf(".");
      i++;
    }
}

void print_line(t_section_printer *print, int *pos)
{
  int i;
	int j;
	int strpos;
	char str[16];

  i = 0;
	j = 0;
	strpos = 0;
  while (i < 4)
	{
		while (j < 4)
			{
			  if (*pos < print->sh_size)
			    {
			      printf("%02x", *print->section & 0xff);
			      str[strpos] = *print->section;
			      print->section++;
			      strpos++;
			    }
			  else
			    {
            printf("  ");
			      str[strpos] = ' ';
			      strpos++;
			    }
			  (*pos)++;
			  j++;
			}
		  j = 0;
		printf(" ");
		i++;
	}
	print_str(str);
}

void print_section(char *section, t_data_info *info, int pos)
{
	t_section_printer print;
	int i;

	i = 0;
	print.sh_addr = info->shdr[pos].sh_addr;
  print.sh_size = (int)info->shdr[pos].sh_size;
	print.section = section;
	printf("Contents of section %s:\n", &info->strtab[info->shdr[pos].sh_name]);
  print.addr_format = sh_addr_format(print.sh_addr, print.sh_size);
	while (i < print.sh_size)
    {
		  printf(" %0*x ", print.addr_format, print.sh_addr);
		  print_line(&print, &i);
		  print.sh_addr += 16;
		  printf("\n");
    }
}

void print_all_section(t_data_info *info)
{
  int i;
	char *section;

  i = 0;
	section = (char*)info->elf_header;
  while (i < info->shnum)
    {
      section += info->shdr[i].sh_offset;
		  if (is_section_to_print(info, i, info->shdr[i].sh_type))
			  print_section(section, info, i);
		  section = (char *)info->elf_header;
		  i++;
		}
}
