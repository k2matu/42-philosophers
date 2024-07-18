# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 11:54:18 by kmatjuhi          #+#    #+#              #
#    Updated: 2024/07/18 21:19:17 by kmatjuhi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = 	main.c \
		error.c \
		init.c \
		monitor.c \
		msg.c \
		p_atol.c \
		routine.c \
		time_func.c \
		tread.c \

OFILES	=	$(SRCS:.c=.o)

CC		=	cc
RM		=	-rm -f
CFLAGS	=	-Wall -Wextra -Werror
LDFLAGS =	-pthread

all:		$(NAME)

$(NAME):	$(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OFILES)
	
fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
