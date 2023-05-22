NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf
LDFLAGS = -L/opt/homebrew/opt/readline/lib
CPPFLAGS = -I/opt/homebrew/opt/readline/include
LIBFT = libft/libft.a
SRC = main.c $(LIBFT)
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CPPFLAGS) -lreadline $(LDFLAGS) $(OBJ) -o $(NAME) -Llibft -lft

%.o: %.c
	$(CC) $(CPPFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

clean:
	$(RM) $(OBJ)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all

.PHONY : all clean fclean re
