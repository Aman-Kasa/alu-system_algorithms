CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g -I.. -I../heap

SRC = main.c \
      ../symbol.c \
      ../huffman_priority_queue.c \
      ../huffman_extract_and_insert.c \
      ../huffman_tree.c

OBJ = $(SRC:.c=.o)
NAME = huffman

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
