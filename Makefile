##
## Makefile for  in /home/jacqui_p/rendu/PSU_2016_nmobjdump/
##
## Made by Pierre-Emmanuel Jacquier
## Login   <jacqui_p@epitech.eu>
##
## Started on  Wed Feb 22 11:36:14 2017 Pierre-Emmanuel Jacquier
## Last update Thu Feb 23 15:22:09 2017 Pierre-Emmanuel Jacquier
##

CC	= cc

RM	= rm -f

CFLAGS	+= -I. -Wall -Wextra

NAMEOBJ	= my_objdump

NAMENM = my_nm

SRCSOBJ	= objdump.c

SRCSNM	= nm.c

OBJSOBJ	= $(SRCSOBJ:.c=.o)

OBJSNM	= $(SRCSNM:.c=.o)

compobjobj:
	$(CC) -c $(SRCSOBJ)

compobjnm:
	$(CC) -c $(SRCSNM)

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
