# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 05:10:13 by rschlott          #+#    #+#              #
#    Updated: 2022/11/17 15:38:56 by rschlott         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES		=	server.c	\
				client.c

OBJECTS		=	$(SOURCES:.c=.o)

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

all: server client

server: server.o libft
		$(CC) -o $@ $< -Llibft -lft

client: client.o libft
		$(CC) -o $@ $< -Llibft -lft

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

libft:
		make -C libft

clean:
		rm -rf $(OBJECTS)
		make -C libft clean
	
fclean: clean
		rm -rf server client libft/libft.a

re: fclean all

.PHONY: all libft clean fclean re