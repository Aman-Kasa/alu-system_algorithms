CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g -I.. -I../heap

# Explicitly pull all source files, including parent directory and heap dependencies
SRC = main.c \
      ../symbol.c \
      ../huffman_priority_queue.c \
      ../huffman_extract_and_insert.c \
      ../huffman_tree.c

# Dynamically include any provided static library source or manual file from parent
# to handle binary_tree_node definition securely
PARENT_C = $(wildcard ../*.c)
HEAP_C = $(wildcard ../heap/*.c)

# Combine everything cleanly into the build pipeline
ALL_SRC = $(SRC) $(HEAP_C)
OBJ = $(ALL_SRC:.c=.o)
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
