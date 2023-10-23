/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:33:26 by agan              #+#    #+#             */
/*   Updated: 2023/10/17 15:33:27 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// dup2 helper function for error handling
void	ft_dup(int to, int from)
{
	if (dup2(to, from) < 0)
		ft_error(3);
}

// Call env functions and exec
void	ft_exec(char **env, char *cmd)
{
	char	**allpath;
	char	**args;
	char	*path;

	allpath = ft_getenv(env);
	args = arr_split(cmd, ' ');
	path = ft_getpath(allpath, args[0]);
	if (path)
		execve(path, args, env);
	ft_error(0);
	ft_free(args);
	exit(127);
}

// Error handling for command not found, pipe, fork, redirection and invalid args error
void	ft_error(int num)
{
	if (num == 0)
	{
		ft_putstr_fd("pipex: command not found\n", 2);
		exit(127);
	}
	if (num == 1)
	{
		ft_putstr_fd("error: unable to pipe\n", 2);
		exit(126);
	}
	if (num == 2)
	{
		ft_putstr_fd("error: unable to fork\n", 2);
		exit(127);
	}
	if (num == 3)
	{
		ft_putstr_fd("error: pipes redirection\n", 2);
		exit(9);
	}
	if (num == 4)
		ft_putstr_fd("invalid arg: ./pipex file1 cmd1 cmd2 ... cmdn file2\n", 2);
}

// Open files and check for errors
int	ft_openfiles(int *infile, int *outfile, int argc, char **argv)
{
	*infile = open(argv[1], O_RDONLY);
	if (*infile < 0)
	{
		ft_putstr_fd("error: unable to open file", 2);
		exit(errno);
	}
	*outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*outfile < 0)
	{
		ft_putstr_fd("error: unable to open file", 2);
		exit(errno);
	}
	return (0);
}

// Opens here_doc file and check for errors
int	open_heredoc(int *outfile, char *filename)
{
	*outfile = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*outfile < 0)
	{
		ft_putstr_fd("error: unable to open file", 2);
		exit(errno);
	}
	return (0);
}
