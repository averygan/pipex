/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:56:17 by agan              #+#    #+#             */
/*   Updated: 2023/10/17 13:56:18 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include "../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

/* utils functions */
int		ft_openfiles(int *infile, int *outfile, int argc, char **argv);
void	ft_error(int num, char *cmd);
int		open_heredoc(int *outfile, char *filename);
void	ft_exec(char **env, char *cmd);
void	ft_dup(int to, int from);

/* env functions */
void	ft_free(char **s);
char	*ft_getpath(char **allpath, char *cmd);
char	**ft_getenv(char **env);

/* split functions */
int		token_count(char *s, char c);
char	**arr_split(char *s, char c);
void	alloc_words(char **words, char *s, char c);

/* get next line and here_doc functions */
char	*get_next_line(int fd);
char	*ft_join(char *res, char *buf);
char	*ft_clean(char *buf);
char	*ft_read(int fd, char *res);
char	*ft_next(char *buf);
void	here_doc(char *limiter);

#endif