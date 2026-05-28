CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -I../heap -I../
SRC = ../heap/heap_create.c ../heap/binary_tree_node.c ../heap/heap_insert.c \
      ../heap/heap_extract.c ../heap/heap_delete.c ../symbol.c \
      ../huffman_priority_queue.c ../huffman_extract_and_insert.c \
      ../huffman_tree.c ../huffman_codes.c main.c
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
