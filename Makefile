# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: itsuman <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/10 18:22:44 by itsuman           #+#    #+#              #
#    Updated: 2017/03/30 17:48:56 by itsuman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME =	filler
FLAGS = -Wall -Werror -Wextra -g
SRC = main.c get_coordinate.c fill_coordinate.c get_next_line.c
OSRC =	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OSRC)
	make -C libft
	gcc -o $(NAME) $(FLAGS) $(OSRC) libft/libft.a

%.o: %.c
	gcc $(FLAGS) -c -o $@ $<

clean:
	make clean -C libft
	rm -f $(OSRC)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all
