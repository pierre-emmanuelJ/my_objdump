##
## Makefile for  in /home/jacqui_p/rendu/PSU_2016_nmobjdump/
##
## Made by Pierre-Emmanuel Jacquier
## Login   <jacqui_p@epitech.eu>
##
## Started on  Wed Feb 22 11:36:14 2017 Pierre-Emmanuel Jacquier
## Last update Wed Feb 22 11:46:54 2017 Pierre-Emmanuel Jacquier
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

objdump: $(NAMEOBJ)

	$(NAMEOBJ): $(OBJSOBJ)
	$(CC) -o $(NAMEOBJ) $(OBJSOBJ)

nm: $(NAMENM)

$(NAMENM): $(OBJSNM)
	$(CC) -o $(NAMENM) $(OBJSNM)

all: objdump nm

clean:
	$(RM) $(OBJSOBJ)
	$(RM) $(OBJSNM)

fclean: clean
	$(RM) $(NAMEOBJ)
	$(RM) $(NAMENM)

re: fclean all

.PHONY: all clean fclean re
