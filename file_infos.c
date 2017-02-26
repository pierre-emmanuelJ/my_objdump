/*
** file_infos.c for  in /home/jacqui_p/rendu/PSU_2016_nmobjdump/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Sun Feb 26 12:28:18 2017 Pierre-Emmanuel Jacquier
** Last update Sun Feb 26 12:29:00 2017 Pierre-Emmanuel Jacquier
*/

#include "objdump.h"

int     filesize(int fd)
{
  return (lseek(fd, 0, SEEK_END));
}

int     open_file(char *path, int *fd, char *file)
{
  if ((*fd = open(path, O_RDONLY)) == -1)
    {
      fprintf(stderr, "%s: '%s': No such file\n", file, path);
      close(*fd);
      return (0);
    }
  return (1);
}

int             is_regular_file(const char *path)
{
  struct stat   path_stat;

  stat(path, &path_stat);
  return (S_ISREG(path_stat.st_mode));
}

int             is_empty_file(const char *path)
{
  struct stat   path_stat;

  stat(path, &path_stat);
  return (path_stat.st_size == 0);
}
