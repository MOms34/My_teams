##
## EPITECH PROJECT, 2023
## epitech
## File description:
## momo
##

CC 		= 	gcc

MAIN	=	src/server/main/main.c

MAIN_CLIENT	=	src/client/main/main.c

FILES	=	$(wildcard ./src/server/*.c)

FILES_CLIENT	=	$(wildcard ./src/client/*.c)

SRC 	=	$(MAIN)		\
			$(FILES)
SRC_CLIENT 	=	$(MAIN_CLIENT)		\
				$(FILES_CLIENT)

RM 		= 	rm -f

NAME 	= 	myteams_server
NAME_CLIENT 	= 	myteams_cli

CFLAGS 	= 	-Wall -Werror -I include/ -luuid -L./libs/myteams -lmyteams

OBJ		=	$(SRC:.c=.o)
OBJJ	=	$(SRC_CLIENT:.c=.o)

all: $(NAME) $(NAME_CLIENT)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

$(NAME_CLIENT): $(OBJJ)
	$(CC) -o $(NAME_CLIENT) $(OBJJ) $(CFLAGS)

clean:
	$(RM) $(OBJ)
	$(RM) $(OBJJ)
	find . -name '*~' -delete -o -name '#*#' -delete -o -name '*.gcno' \
		-delete -o -name -'*.gcdo' -delete -o -name '*.gcda' -delete

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_CLIENT)
	$(RM) $(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re
