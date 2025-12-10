NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./
AR = ar rcs
RM = rm -f

SRC = pipex.c \
		utils/check_absolute.c utils/closing_processes.c utils/error_print.c utils/exec_processes.c utils/free_related.c utils/pipex_utils.c utils/bonus_utils.c utils/ft_findstr.c \
		lst_related/init_files.c lst_related/init_list.c
OBJ = $(SRC:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	make -C ./ft_printf
	make -C ./get_next_line
	cp libft/libft.a $(NAME)
	cp ft_printf/libftprintf.a $(NAME)
	cp get_next_line/libgnl.a $(NAME)
	$(CC) $(CFLAGS) $(OBJ) -L./ft_printf -lftprintf -L./libft -lft  -L./get_next_line -lgnl -o $@

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	make -C ft_printf clean
	make -C get_next_line clean
	$(RM) $(OBJ)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	make -C ft_printf fclean
	make -C get_next_line fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
