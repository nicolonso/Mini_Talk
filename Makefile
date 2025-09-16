#Standard

NAME  = client
NAME  = server

#Directories
LIBFT				= ./Lib/libft.a
HDR					= hdr/
SRC_DIR				= src/
OBJ_DIR				= obj/

# Compiler and CFlags

CC					= cc
CFLAGS				= -Wall -Wextra -Werror -I$(HDR)
RM					= rm -fclean

# Source Files

CLIENT_DIR			= $(SRC_DIR)client/client.c\

SERVER_DIR			= $(SRC_DIR)server/server.c

# Concatenate all sources
SRCS				= $(CLIENT_DIR) $(SERVER_DIR)

OBJ					= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

start:
					@make all

$(LIBFT):
					@make -C ./Lib

all:				$(NAME)

$(NAME):			$(OBJ) $(LIBFT)
					@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c 
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) -c $< -o $@

clean:
					@$(RM) -r $(OBJ_DIR)
					@make clean -C ./Lib

fclean: 			clean
					@$(RM) $(NAME)
					@$(RM) $(LIBFT)

re: 				fclean all

# Phony targets represent actions not files
.PHONY: 			start all clean fclean re