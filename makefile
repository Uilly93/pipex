NAME = pipex
INCLUDES = libft/
CC = cc
LIBFT = libft/
SRC_DIR = src
OBJ_DIR = obj
SRC_NAME = pipex.c
OBJS = $(addprefix $(OBJ_DIR)/,$(SRC_NAME:%.c=%.o))
SRC = $(addprefix $(SRC_DIR)/,$(SRC_NAME))
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -rf

all: libft $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT) -lft

clean:
	$(RM) $(OBJ_DIR)
	cd $(LIBFT) && make clean

fclean: clean
	$(RM) $(NAME)
	cd $(LIBFT) && make fclean

re: fclean all

valgrind: all
	valgrind --trace-children --track-fds  

libft:
	$(MAKE) -C $(LIBFT)

.PHONY: all clean fclean re libft