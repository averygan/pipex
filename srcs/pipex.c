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

// Fork process
// Child process cats file1
// dup2 to redirect stdout to cmd1
// Use split to obtain char **

int	main(int argc, char *argv[])
{
	int pipes[2];
	int	pid;
	int pid2;
	char **args;

	if (pipe(pipes) < 0)
		return 2;
	pid = fork();
	pid2 = fork();
	if (pid < 0)
		return 3;
	// In child process, cat file
	if (pid == 0)
	{
		(void)argc;
		close(pipes[0]);
		// Redirect stdout to write pipe
		dup2(pipes[1], STDOUT_FILENO);
		execve("/bin/cat", (char *[]){"cat", argv[1], NULL}, NULL);
		close(pipes[1]);
	}
	// In parent process, read from pipe and exec
	else
	{
		close(pipes[1]);
		dup2(pipes[0], STDIN_FILENO);
		args = ft_split(argv[2], ' ');
		execve("/bin/grep", args, NULL);
		close(pipes[0]);
		wait(NULL);
	}
	return (0);
}