/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:47:42 by agan              #+#    #+#             */
/*   Updated: 2023/10/10 15:47:43 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

// Pipe handling and calls redirect function for child process, exec cmd
void	child_process(char **argv, int *pipes, char **env)
{
	int	fd;

	close(pipes[0]);
	fd = ft_openfiles(argv, 0);
	ft_redirect(&fd, &pipes[1]);
	close(pipes[1]);
	ft_exec(env, argv[2]);
	return ;
}

// Pipe handling and calls redirect function for parent process, exec cmd
void	parent_process(char **argv, int *pipes, char **env)
{
	int	outfd;

	close(pipes[1]);
	outfd = ft_openfiles(argv, 1);
	ft_redirect(&pipes[0], &outfd);
	close(pipes[0]);
	ft_exec(env, argv[3]);
	wait(NULL);
	return ;
}

int	main(int argc, char *argv[], char **envp)
{
	int	pipes[2];
	int	pid;

	if (argc == 5)
	{
		if (pipe(pipes) < 0)
			ft_error(1, NULL);
		pid = fork();
		if (pid < 0)
			ft_error(2, NULL);
		if (!pid)
			child_process(argv, pipes, envp);
		else
			parent_process(argv, pipes, envp);
	}
	else
		ft_error(3, NULL);
	return (1);
}
