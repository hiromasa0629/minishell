# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/30 15:26:10 by hyap              #+#    #+#              #
#    Updated: 2022/08/04 20:02:44 by hyap             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = $(wildcard srcs/*.c srcs/lexer/*.c srcs/utils/*.c srcs/parser/*.c)

CFLAGS = -Wall -Werror -Wextra

CC = gcc

OBJ = $(SRCS:.c=.o)

INCLUDES = -I includes -I ./readline-8.1/include

NAME = minishell

LIB = -L ./lib -lreadline -L ./readline-8.1/lib

RM = rm -f

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(LIB) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
