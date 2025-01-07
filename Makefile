<<<<<<< HEAD
NAME	=	hashdog

SRC		=	main.c						\
			functions/arguments.c		\
			functions/bruteforce.c		\
			functions/checkDigest.c		\
			functions/dictAtk.c			\
			functions/config.c

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-Wall #-Wextra -iquote include
LDFLAGS	=	-lcrypto

all:	$(NAME)

$(NAME):	$(OBJ)
	@gcc -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re:	fclean all
=======
NAME    =   hashdog

SRC     =   main.c					\
			functions/arguments.c	\
			functions/bruteforce.c	\
			functions/checkDigest.c	\
			functions/dictAtk.c		\
			functions/config.c

OBJ     =   $(SRC:.c=.o)

CFLAGS  =   -Wall -Wextra -iquote include $(shell pkg-config --cflags gtk4 openssl)
LDFLAGS =   $(shell pkg-config --libs gtk4 openssl)

all:		$(NAME)

$(NAME):	$(OBJ)
			@gcc -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

clean:
			@rm -f $(OBJ)

fclean: 	clean
			@rm -f $(NAME)

re: 		fclean all

>>>>>>> dbc4c29506f54b019524cdf595c5b7ab00ccfadd
