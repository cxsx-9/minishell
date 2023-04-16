NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf
SRC = main.c
OBJ = $(SRC:.c=.o)
LFLAGS = -L/opt/homebrew/opt/readline/lib
CPPFLAGS = -I/opt/homebrew/opt/readline/include


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CPPFLAGS) -lreadline $(LFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all

.PHONY : all clean fclean re
