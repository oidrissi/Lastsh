# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/14 20:58:16 by oidrissi          #+#    #+#              #
#    Updated: 2021/11/17 00:10:45 by oidrissi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -pthread -Wall -Wextra -Werror -lreadline
NAME = hell420

SRC = minishell.c\
		helpers.c\
		ft_alloc.c\

all: $(NAME)

$(NAME): $(SRC)
	@$(CC) $(SRC) $(FLAGS) -o $(NAME)

clean:
	@rm -rf $(NAME)

fclean: clean

re: fclean all