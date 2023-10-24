/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:36:47 by agan              #+#    #+#             */
/*   Updated: 2023/10/11 15:36:50 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include "../libft/libft.h"

/* utils */
void	ft_error(int num, char *cmd);
void	ft_redirect(int *in, int *out);
int		ft_openfiles(char **argv, int num);

/* env functions */
void	ft_free(char **s);
char	*ft_getpath(char **allpath, char *cmd);
char	**ft_getenv(char **env);

/* split functions */
int		token_count(char *s, char c);
char	**arr_split(char *s, char c);
void	alloc_words(char **words, char *s, char c);

#endif
