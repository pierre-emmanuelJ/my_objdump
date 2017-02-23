##
## Makefile for  in /home/jacqui_p/rendu/PSU_2016_nmobjdump/
##
## Made by Pierre-Emmanuel Jacquier
## Login   <jacqui_p@epitech.eu>
##
## Started on  Wed Feb 22 11:36:14 2017 Pierre-Emmanuel Jacquier
## Last update Thu Feb 23 19:29:33 2017 Pierre-Emmanuel Jacquier
##

CC	= cc

RM	= rm -f

CFLAGS	+= -I. -Wall -Wextra -g

NAMEOBJ	= my_objdump

NAMENM = my_nm

SRCSOBJ	= objdump.c \
          flags_header.c \
          architecture.c \
					elf_check.c \
					print_sections_content.c


SRCSNM	= nm.c

OBJSOBJ	= $(SRCSOBJ:.c=.o)

OBJSNM	= $(SRCSNM:.c=.o)

compobjobj:
	$(CC) $(CFLAGS) -c $(SRCSOBJ)

compobjnm:
	$(CC) $(CFLAGS) -c $(SRCSNM)

objdump: compobjobj
	$(CC) -o my_objdump $(OBJSOBJ)

nm: compobjnm
	$(CC) -o my_nm $(OBJSNM)

all: objdump nm

clean:
	$(RM) $(OBJSOBJ)
	$(RM) $(OBJSNM)

fclean: clean
	$(RM) $(NAMEOBJ)
	$(RM) $(NAMENM)

re: fclean all

.PHONY: all clean fclean re
