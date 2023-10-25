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
	ft_error(0, cmd);
	ft_free(args);
	exit(127);
}

// Function to open outfile, infile and heredoc outfile
int	ft_openfile(char *filename, int num)
{
	int	fd;

	if (num == 0)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (num == 1)
		fd = open(filename, O_RDONLY);
	if (num == 2)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("pipex: line 1: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(errno);
	}
	return (fd);
}

// Helper function for main process
void	ft_outfile(int outfile, char **envp, char **argv, int i)
{
	ft_dup(outfile, STDOUT_FILENO);
	ft_exec(envp, argv[i]);
}
