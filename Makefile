# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agan <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/11 10:42:44 by agan              #+#    #+#              #
#    Updated: 2023/10/11 10:42:45 by agan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
SRCS	= srcs/pipex.c srcs/utils.c srcs/pipex_split.c srcs/env.c
OBJS 	= ${SRCS:.c=.o}
MAIN	= srcs/pipex.c
CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror
LIBFT_BUILD := ./libft/libft.a

all: ${NAME}

${NAME} : ${OBJS} ${LIBFT_BUILD}
	@$(CC) ${CFLAGS} ${OBJS} -Llibft -lft -o ${NAME}
	@echo "Pipex Compiled!"

${LIBFT_BUILD}:
	@make -C ./libft

clean:
	@make clean -C ./libft
	@rm -f ${OBJS}

fclean: clean
	@make fclean -C ./libft
	@rm -f ${NAME}
	@echo "fclean Completed!"

re: fclean all