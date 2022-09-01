# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/30 15:26:10 by hyap              #+#    #+#              #
#    Updated: 2022/08/30 17:30:04 by hyap             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = $(wildcard srcs/*.c srcs/lexer/*.c srcs/utils/*.c srcs/parser/*.c srcs/executors/*.c srcs/builtins/*.c)

CFLAGS = -Wall -Werror -Wextra

CC = gcc

OBJ = $(SRCS:.c=.o)

INCLUDES = -I includes -I ./readline-8.1/include

NAME = minishell

LIB = -L ./lib -lreadline -L ./readline-8.1/lib

RM = rm -f

LEAKS = -g -fsanitize=address

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(LEAKS) $(LIB) $(OBJ) -o $(NAME)

test: $(NAME)
	./minishell

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
