/*
** test.c for  in /home/jacqui_p/rendu/PSU_2016_nmobjdump/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed Feb 22 10:15:05 2017 Pierre-Emmanuel Jacquier
** Last update Fri Feb 24 21:23:10 2017 Pierre-Emmanuel Jacquier
*/

#include "objdump.h"

int filesize(int fd)
{
  return (lseek(fd, 0, SEEK_END));
}

void objdump32(void *data, char *file)
{
  t_data_info info;

  info.flags = 0;
  printf("\n%s:     file format elf32-i386\n", file);
  info.elf32_header = (Elf32_Ehdr*)data;
  info.shnum = info.elf32_header->e_shnum;
  info.shdr32 = (Elf32_Shdr*)(data + info.elf32_header->e_shoff);
  get_flag_value32(&info);
  printf("architecture: i386, flags 0x%08x:\n", info.flags);
  print_bitset(info.flags);
  printf("start address 0x%08zx\n\n", (size_t)(info.elf32_header->e_entry));
  info.strtab = (char*)(data + info.shdr32[info.elf32_header->e_shstrndx].sh_offset);
  print_all_section32(&info);

}

void objdump64(void *data, char *file)
{
  t_data_info info;

  info.flags = 0;
  printf("\n%s:     file format elf64-x86-64\n", file);
  info.elf64_header = (Elf64_Ehdr*)data;
  info.shnum = info.elf64_header->e_shnum;
  info.shdr64 = (Elf64_Shdr*)(data + info.elf64_header->e_shoff);
  get_flag_value64(&info);
  printf("architecture: i386:x86-64, flags 0x%08x:\n", info.flags);
  print_bitset(info.flags);
  printf("start address 0x%016zx\n\n", (info.elf64_header->e_entry));
  info.strtab = (char*)(data + info.shdr64[info.elf64_header->e_shstrndx].sh_offset);
  print_all_section64(&info);
}

void objdump(char *file, int fd)
{
  void				*data;
  size_t			datasize;

  if (!is_regular_file(file))
  {
    fprintf(stderr, "objdump: Warning: '%s' is not an ordinary file\n", file);
    return ;
  }
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

int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return (S_ISREG(path_stat.st_mode));
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
