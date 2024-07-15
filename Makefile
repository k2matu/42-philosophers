# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 11:54:18 by kmatjuhi          #+#    #+#              #
#    Updated: 2024/07/15 09:27:32 by kmatjuhi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = 	philo.c \
		time_in_ms.c \
		atol.c \
		msg.c \
		tread.c \
		init.c \
		routine.c \
		error.c

OFILES	=	$(SRCS:.c=.o)

CC		=	cc
RM		=	-rm -f
CFLAGS	=	-pthread -Wall -Wextra -Werror -g

all:		$(NAME)

$(NAME):	$(OFILES)

%.o: %.c
		$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(OFILES)
	
fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
