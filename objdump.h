/*
** objdump.h for  in /home/jacqui_p/rendu/PSU_2016_nmobjdump/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed Feb 22 11:54:09 2017 Pierre-Emmanuel Jacquier
** Last update Thu Feb 23 14:47:35 2017 Pierre-Emmanuel Jacquier
*/

#ifndef OBJDUBP_H_
# define OBJDUBP_H_

#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#include "flags.h"

typedef struct s_data_info
{
  
}              t_data_info;

#define PRINTER(x, comma) printf("%s%s", comma, x); comma = ", ";

#endif /* !OBJDUBP_H_ */
