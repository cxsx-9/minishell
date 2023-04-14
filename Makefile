NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf
SRC = main.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include -lreadline

clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all

.PHONY : all clean fclean re
