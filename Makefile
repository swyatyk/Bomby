CC = gcc
NAME = Bomberman
RM = rm -f
CFLAGS = -Wall -Wextra
SDLFLAGS = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lfreetype
SRC =	./src/main.c \
		./src/map.c \
		./src/playerMove.c \
		./src/animationPlayer.c \
		./src/server.c \
		./src/bomber.c


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
