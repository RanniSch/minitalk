# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 05:10:13 by rschlott          #+#    #+#              #
#    Updated: 2022/11/21 05:58:19 by rschlott         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES		=	server.c	\
				client.c	\
				minitalk_utils.c

OBJECTS		=	$(SOURCES:.c=.o)

CC			=	gcc

CFLAGS		=	-c -Wall -Wextra -Werror

all: server client

server: server.o minitalk_utils.o
		$(CC) -o $@ $^

client: client.o minitalk_utils.o
		$(CC) -o $@ $^

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -rf $(OBJECTS)
	
fclean: clean
		rm -rf server client

re: fclean all