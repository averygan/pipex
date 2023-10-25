/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:52:58 by agan              #+#    #+#             */
/*   Updated: 2023/10/17 13:52:59 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// Create pipe, fork child process
// Pipe handling for child and parent
// Redirection for parent and child processes
// Exec for child process
void	pipe_handler(char *cmd, char **env)
{
	int	pipes[2];
	int	pid;

	if (pipe(pipes) < 0)
		ft_error(1, NULL);
	pid = fork();
	if (pid < 0)
		ft_error(2, NULL);
	if (!pid)
	{
		close(pipes[0]);
		ft_dup(pipes[1], STDOUT_FILENO);
		ft_exec(env, cmd);
	}
	else
	{
		close(pipes[1]);
		ft_dup(pipes[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

// Helper function for here_doc - Reads until limiter found
void	heredoc_next(char *limiter, int *pipes)
{
	char	*res;

	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", 1);
		res = get_next_line(STDIN_FILENO);
		if (!res)
			exit(EXIT_SUCCESS);
		if (ft_strncmp(res, limiter, ft_strlen(limiter)) == 0
			&& (ft_strlen(res) - 1 == ft_strlen(limiter)))
		{
			free(res);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(res, pipes[1]);
		free(res);
	}
}

// here_doc handling
// Creates pipes, forks child process
// Redirect parent process to read from child's stdin
// Pipe handling for parent and child
void	here_doc(char *limiter)
{
	int	pipes[2];
	int	pid;

	if (pipe(pipes) < 0)
		ft_error(1, NULL);
	pid = fork();
	if (pid < 0)
		ft_error(2, NULL);
	if (!pid)
	{
		close(pipes[0]);
		heredoc_next(limiter, pipes);
		close(pipes[1]);
	}
	else
	{
		close(pipes[1]);
		ft_dup(pipes[0], STDIN_FILENO);
		close(pipes[0]);
	}
}

// Function to create pipe, fork process, open infile and exec cmd1
void	ft_infile(char **argv, char **env)
{
	int	pipes[2];
	int	pid;
	int	infile;

	if (pipe(pipes) < 0)
		ft_error(1, NULL);
	pid = fork();
	if (pid < 0)
		ft_error(2, NULL);
	if (!pid)
	{
		close(pipes[0]);
		infile = ft_openfile(argv[1], 1);
		ft_dup(infile, STDIN_FILENO);
		ft_dup(pipes[1], STDOUT_FILENO);
		ft_exec(env, argv[2]);
		close(pipes[1]);
	}
	else
	{
		close(pipes[1]);
		ft_dup(pipes[0], STDIN_FILENO);
		close(pipes[0]);
	}
}

// Main function checks for argument
// Checks if here_doc or infile
int	main(int argc, char *argv[], char **envp)
{
	int	i;
	int	outfile;

	i = 3;
	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			outfile = ft_openfile(argv[argc - 1], 2);
			here_doc(argv[2]);
		}
		else
		{
			ft_infile(argv, envp);
			outfile = ft_openfile(argv[argc - 1], 0);
		}
		while (i < argc - 2)
			pipe_handler(argv[i++], envp);
		ft_outfile(outfile, envp, argv, i);
	}
	else
		ft_error(4, NULL);
	return (0);
}
