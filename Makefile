NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes/
AR = ar rcs
RM = rm -f

SRC = pipex.c pipex_utils.c
OBJ = $(SRC:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	make -C ./ft_printf
	cp libft/libft.a $(NAME)
	cp ft_printf/libftprintf.a $(NAME)
	$(CC) $(CFLAGS) $(OBJ) -L./ft_printf -lftprintf -L./libft -lft -o $@

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	make -C ft_printf clean
	$(RM) $(OBJ)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	make -C ft_printf fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
