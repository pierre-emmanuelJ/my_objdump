/*
** test.c for  in /home/jacqui_p/rendu/PSU_2016_nmobjdump/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed Feb 22 10:15:05 2017 Pierre-Emmanuel Jacquier
** Last update Thu Feb 23 15:03:04 2017 Pierre-Emmanuel Jacquier
*/

#include "objdump.h"

int filesize(int fd)
{
  return (lseek(fd, 0, SEEK_END));
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

int iself_file(void *data, size_t datasize)
{
  char *file;

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

void objdump32(void *data, char *file)
{
  // Elf32_Ehdr	*elf_header;
  // Elf32_Shdr	*shdr;
  // char				*strtab;
  //
  //
  // elf_header = (Elf32_Ehdr*)data;
  // printf("%s:     file format elf32-i386\n", file);
  //
  // printf("architecture: i386, flags %x:\n", flags);
  // shdr = (Elf32_Shdr*)(data + elf_header->e_shoff);
  // strtab = (char*)(data + shdr[elf_header->e_shstrndx].sh_offset);
  // print_sh_name32(shdr, strtab, elf_header->e_shnum);
}

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

void get_flag_value(int *flags, Elf64_Ehdr *elf_header, Elf64_Shdr	*shdr, int shnum)
{
  int i;

  i = 0;
  bitset_flagheader(flags, elf_header->e_type);
  while (i < shnum)
    {
      bitset_flagsections(flags, shdr[i].sh_type);
      i++;
    }
}

void objdump64(void *data, char *file)
{
  Elf64_Ehdr	*elf_header;
  Elf64_Shdr	*shdr;
  char				*strtab;
  int					flags;

  flags = 0;
  printf("\n%s:     file format elf64-x86-64\n", file);
  elf_header = (Elf64_Ehdr*)data;
  shdr = (Elf64_Shdr*)(data + elf_header->e_shoff);
  get_flag_value(&flags, elf_header, shdr, elf_header->e_shnum);
  printf("architecture: i386:x86-64, flags 0x%08x:\n", flags);
  print_bitset(flags);
  printf("start address 0x%016zx\n\n", (elf_header->e_entry));
  strtab = (char*)(data + shdr[elf_header->e_shstrndx].sh_offset);
  print_sh_name64(shdr, strtab, elf_header->e_shnum);
}

void objdump(char *file, int fd)
{
  void				*data;
  size_t			datasize;

  datasize = filesize(fd);
  data = mmap(NULL, datasize, PROT_READ, MAP_SHARED, fd, 0);
  if (!iself_file(data, datasize))
    {
      fprintf(stderr, "objdump: %s: File format not recognized\n", file);
      return ;
    }
  if (what_architecture(data, datasize) == ELFCLASS32)
    objdump32(data, file);
  else if(what_architecture(data, datasize) == ELFCLASS64)
    objdump64(data, file);
  else
    fprintf(stderr, "objdump: %s: File format not recognized\n", file);
}

int open_file(char *path, int *fd)
{
  if ((*fd = open(path, O_RDONLY)) == -1)
    {
      fprintf(stderr, "my_objdump: '%s': No such file\n", path);
      close(*fd);
      return (0);
    }
  return (1);
}

int main(int argc, char **argv)
{
  int i;
  int fd;

  i = 1;
  if (argc == 1)
    {
      if (open_file("a.out", &fd))
        {
          objdump("a.out", fd);
          close(fd);
        }
      return (0);
    }
  while (i < argc)
    {
      if (open_file(argv[i], &fd))
        {
          objdump(argv[i], fd);
          close(fd);
        }
      i++;
    }
  return (0);
}
