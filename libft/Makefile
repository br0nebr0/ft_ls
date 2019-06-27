# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: waeron-g <waeron-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 21:15:15 by waeron-g          #+#    #+#              #
#    Updated: 2019/02/27 17:29:42 by waeron-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = ft_*.c
OBJ = *.o

all: $(NAME)
$(NAME): $(SRC)
	gcc -Wall -Wextra -Werror -c -g $(SRC) -I includes/
	ar rcs $(NAME) $(OBJ)
clean:
	/bin/rm -f $(OBJ)
fclean: clean
	/bin/rm -f $(NAME)
re: fclean all
