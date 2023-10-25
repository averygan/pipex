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
SRCS	= srcs/pipex.c srcs/utils.c srcs/split.c srcs/env.c
SRCS_BONUS = srcs_bonus/pipex_bonus.c srcs_bonus/utils_bonus.c srcs_bonus/split_bonus.c \
				srcs_bonus/env_bonus.c srcs_bonus/get_next_line_bonus.c srcs_bonus/errors_bonus.c
OBJS 	= ${SRCS:.c=.o}
OBJS_BONUS = ${SRCS_BONUS:.c=.o}
CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror
LIBFT_BUILD := ./libft/libft.a

all: ${NAME}

${NAME} : ${OBJS} ${LIBFT_BUILD}
	@$(CC) ${CFLAGS} ${OBJS} -Llibft -lft -o ${NAME}
	@echo "Pipex Compiled!"

.c.o:
	@$(CC) ${CFLAGS} -c $< -o $@

${LIBFT_BUILD}:
	@make -s -C ./libft

clean:
	@make -s clean -C ./libft
	@rm -f ${OBJS}
	@rm -f ${OBJS_BONUS}

fclean: clean
	@make -s fclean -C ./libft
	@rm -f ${NAME}
	@echo "fclean Completed!"

re: fclean all

bonus:	${OBJS_BONUS} ${LIBFT_BUILD}
	@$(CC) ${CFLAGS} ${OBJS_BONUS} -Llibft -lft -o ${NAME}
	@echo "Pipex Bonus Compiled!"