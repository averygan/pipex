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

int	main(int argc, char *argv[])
{
	int pipes[2];
	int	pid;
	char **args;

	if (pipe(pipes) < 0)
		return 2;
	pid = fork();
	if (pid < 0)
		return 3;
	int fd = open(argv[1], O_RDONLY);
	// In child process, run grep (cmd1)
	if (pid == 0)
	{
		(void)argc;
		close(pipes[0]);
		// Redirect file1 to stdin
		dup2(fd, STDIN_FILENO);
		dup2(pipes[1], STDOUT_FILENO);
		args = ft_split(argv[2], ' ');
		execve("/bin/grep", args, NULL);
		close(pipes[1]);
	}
	else
	{
	// In parent process, exec wc (cmd2)
		close(pipes[1]);
		// Read from output of cmd1 to stdin 
		dup2(pipes[0], STDIN_FILENO);
		int outfd = open(argv[4], O_WRONLY | O_CREAT, 0644);
		// Redirect output of cmd2 to stdout
		dup2(outfd, STDOUT_FILENO);
		args = ft_split(argv[3], ' ');
		execve("/bin/wc", args, NULL);
		close(pipes[0]);
		wait(NULL);
	}
	return (0);
}