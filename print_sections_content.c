/*
** print_sections_content.c for  in /home/jacqui_p/rendu/PSU_2016_nmobjdump/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Thu Feb 23 16:32:46 2017 Pierre-Emmanuel Jacquier
** Last update Sat Feb 25 20:09:07 2017 Pierre-Emmanuel Jacquier
*/

#include "objdump.h"

static int is_section_to_print64(t_data_info *info, int i, int type)
{
  char *tmp;

  tmp = info->strtab;
  return (!(type == SHT_NULL || info->shdr64[i].sh_size == 0 ||
     type == SHT_SYMTAB || type == SHT_NOBITS ||
     ((info->flags & HAS_RELOC) && (type == SHT_RELA || type == SHT_REL)) ||
     strcmp(&tmp[info->shdr64[i].sh_name], ".shstrtab") == 0 ||
     strcmp(&tmp[info->shdr64[i].sh_name], ".strtab") == 0 ||
     strcmp(&tmp[info->shdr64[i].sh_name], ".symtab") == 0));
}

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

int sh_addr_format(unsigned long addr, int size)
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
  length = length % 16;
    if (i > 6)
      return (6);
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

void print_section_line(unsigned long *pos, int *strpos, t_section_printer *print, char *str)
{
  int j;

  j = 0;
  while (j < 4)
    {
      if (*pos < print->sh_size)
        {
          printf("%02x", *print->section & 0xff);
          str[*strpos] = *print->section;
          print->section++;
          (*strpos)++;
        }
      else
        {
          printf("  ");
          str[*strpos] = ' ';
          (*strpos)++;
        }
      (*pos)++;
      j++;
    }
}

void print_line(t_section_printer *print, unsigned long *pos)
{
  int i;
	int strpos;
	char *str;

  i = 0;
	strpos = 0;
  str = malloc(sizeof(char) * 16);
  while (i < 4)
	{
    print_section_line(pos, &strpos, print, str);
		printf(" ");
		i++;
	}
	print_str(str);
  free(str);
}

void print_section64(char *section, t_data_info *info, int pos)
{
	t_section_printer print;
	unsigned long i;

	i = 0;
	print.sh_addr = info->shdr64[pos].sh_addr;
  print.sh_size = info->shdr64[pos].sh_size;
	print.section = section;
	printf("Contents of section %s:\n", &info->strtab[info->shdr64[pos].sh_name]);
  print.addr_format = sh_addr_format(print.sh_addr, print.sh_size);
	while (i < print.sh_size)
    {
		  printf(" %0*lx ", print.addr_format, print.sh_addr);
		  print_line(&print, &i);
		  print.sh_addr += 16;
		  printf("\n");
    }
}

void print_section32(char *section, t_data_info *info, int pos)
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

void print_all_section64(t_data_info *info)
{
  int i;
	char *section;

  i = 0;
	section = (char*)info->elf64_header;
  while (i < info->shnum)
    {
      section += info->shdr64[i].sh_offset;
		  if (is_section_to_print64(info, i, info->shdr64[i].sh_type))
			  print_section64(section, info, i);
		  section = (char *)info->elf64_header;
		  i++;
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
