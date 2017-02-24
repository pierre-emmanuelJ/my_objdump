/*
** print_sections_content.c for  in /home/jacqui_p/rendu/PSU_2016_nmobjdump/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Thu Feb 23 16:32:46 2017 Pierre-Emmanuel Jacquier
** Last update Fri Feb 24 16:40:13 2017 Pierre-Emmanuel Jacquier
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


int sh_addr_format(int addr, int size)
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

void print_section(char *section, t_data_info *info, int pos)
{
	int line;
	int sh_addr;
	int sh_size;
	int i;
	int j;
	int k;
	char str[20];

	i = 0;
	j = 0;
	k = 0;
	line = 0;
	sh_addr = info->shdr[pos].sh_addr;
  sh_size = (int)info->shdr[pos].sh_size;
	printf("Contents of section %s:\n", &info->strtab[info->shdr[pos].sh_name]);
	while(i < sh_size)
	  {
      printf("%0*x ", sh_addr_format(sh_addr, sh_size), sh_addr);
		  while (j < 16)
			  {
			    while (k < 4)
			      {
			        if (i < sh_size)
			          {
			            printf("%02x", *section);
			            str[j] = *section;
			            section++;
                }
			        else
				        printf(" ");
			        i++;
			        k++;
			        j++;
            }
			    k = 0;
          printf(" ");
		    }
		  j = 0;
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
