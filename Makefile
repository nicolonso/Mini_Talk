# Makefile for Minitalk

# Variables
CC = cc
CFLAGS = -Wall -Wextra -Werror

SERVER_NAME = server
CLIENT_NAME = client

SRC_DIR = src/
OBJ_DIR = obj/

# Source files
SERVER_SRCS = $(SRC_DIR)server.c
CLIENT_SRCS = $(SRC_DIR)client.c
UTILITIES_SRCS = $(SRC_DIR)utilities.c
UTILITIES_TWO_SRCS = $(SRC_DIR)utilities_part_two.c
PRINTF_SRCS = $(SRC_DIR)ft_printf.c

# Object files
SERVER_OBJS = $(OBJ_DIR)server.o $(OBJ_DIR)utilities.o $(OBJ_DIR)utilities_part_two.o $(OBJ_DIR)ft_printf.o
CLIENT_OBJS = $(OBJ_DIR)client.o $(OBJ_DIR)utilities.o $(OBJ_DIR)utilities_part_two.o $(OBJ_DIR)ft_printf.o

# Default rule: Build both server and client
all: $(SERVER_NAME) $(CLIENT_NAME)

# Rule for server
$(SERVER_NAME): $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule for client
$(CLIENT_NAME): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .c to .o
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -rf $(OBJ_DIR)

# Clean everything, including executables
fclean: clean
	rm -f $(SERVER_NAME) $(CLIENT_NAME)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re