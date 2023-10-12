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

// TODO
// Error handling for argument count
// Error handling for all open and exec
// Handle memory leaks

void	ft_child(char **argv, int *pipes, char **args, char **env)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	ft_error(errno);
	dup2(fd, STDIN_FILENO);
	ft_error(errno);
	dup2(pipes[1], STDOUT_FILENO);
	ft_error(errno);
	args = ft_split(argv[2], ' ');
	if (execve(ft_shellpath(args[0]), args, env) < 0)
		ft_error(errno);
}

void	ft_parent(char **argv, int *pipes, char **args, char **env)
{
	int	outfd;

	dup2(pipes[0], STDIN_FILENO);
	ft_error(errno);
	outfd = open(argv[4], O_WRONLY | O_CREAT, 0644);
	ft_error(errno);
	dup2(outfd, STDOUT_FILENO);
	ft_error(errno);
	args = ft_split(argv[3], ' ');
	if (execve(ft_shellpath(args[0]), args, env) < 0)
		ft_error(errno);
}

int	main(int argc, char *argv[], char **envp)
{
	int		pipes[2];
	int		pid;
	char	**args;

	errno = 0;
	pid = 0;
	args = NULL;
	if (argc != 5)
		return (1);
	if (pipe(pipes) < 0)
		ft_error(errno);
	pid = fork();
	if (pid < 0)
		ft_error(errno);
	if (pid == 0)
	{
		close(pipes[0]);
		ft_child(argv, pipes, args, envp);
		close(pipes[1]);
		return (0);
	}
	close(pipes[1]);
	ft_parent(argv, pipes, args, envp);
	close(pipes[0]);
	wait(NULL);
	return (0);
}
