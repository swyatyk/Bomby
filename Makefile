


CC = gcc
NAME = bomberman
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -std=c99
SDLFLAGS = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lfreetype
SRC =	main.c \
		main_menu.c \
		menuJoinGame.c \
		menuHostGame.c \
		map.c \
		userWrite.c \
		playerMove.c \
		animationPlayer.c \
		bomber.c \
		error.c \
		recv.c \
		send.c


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) $(SDLFLAGS) -o $(NAME)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PRONY: all $(NAME) clean fclean re
