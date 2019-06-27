# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ction <ction@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/10 14:36:24 by ction             #+#    #+#              #
#    Updated: 2019/06/10 17:24:23 by waeron-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
SRC = ft_ls.c read_folder.c f_Rls.c ls_output.c
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a
HEADER = -c -I ft_ls.h

all: $(NAME)

$(OBJ): %.o: %.c
		@gcc -c -Wall -Wextra -Werror -I./libft/includes $< -o $@

$(LIBFT):
	@make -C libft

$(NAME): $(LIBFT) $(OBJ)
	@gcc $(OBJ) $(LIBFT) -o $(NAME)

clean:
	/bin/rm -f $(OBJ)
	@make -C libft clean

fclean: clean
	/bin/rm -f $(NAME)
	@make -C libft fclean

re: fclean all
