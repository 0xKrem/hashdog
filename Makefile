NAME    =   hashdog

SRC     =   backend.c       \
            config.c        \
            main.c

OBJ     =   $(SRC:.c=.o)

CFLAGS  =   -Wall -Wextra -iquote include $(shell pkg-config --cflags gtk4 openssl)
LDFLAGS =   $(shell pkg-config --libs gtk4 openssl)

all:    $(NAME)

$(NAME):    $(OBJ)
	@gcc -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

