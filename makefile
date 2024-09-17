# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror

# Directories
LIBFTDIR = ./libft

# Source files
SRCS = 	main.c
OBJS = $(SRCS:%.c=%.o)

# Executable name
NAME = pipex

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -I$(LIBFTDIR) -c $< -o $@

$(NAME): $(OBJS) $(LIBFTDIR)/libft.a
	@$(CC) $(OBJS) -L$(LIBFTDIR) -lft -o $(NAME)

$(LIBFTDIR)/libft.a:
	make -C $(LIBFTDIR)

clean:
	make clean -C $(LIBFTDIR)
	rm -rf $(OBJS)

fclean: clean
	make fclean -C $(LIBFTDIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
