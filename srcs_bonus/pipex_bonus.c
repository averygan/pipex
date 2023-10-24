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
		waitpid(pid, NULL, 0);
		close(pipes[0]);
	}
}

// Helper function for main process
void	parent_handler(int outfile, char **envp, char **argv, int i)
{
	ft_dup(outfile, STDOUT_FILENO);
	ft_exec(envp, argv[i]);
}

// Main function checks for argument
// Checks if here_doc or infile
int	main(int argc, char *argv[], char **envp)
{
	int	infile;
	int	outfile;
	int	i;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			i = 3;
			open_heredoc(&outfile, argv[argc - 1]);
			here_doc(argv[2]);
		}
		else
		{
			i = 2;
			ft_openfiles(&infile, &outfile, argc, argv);
			ft_dup(infile, STDIN_FILENO);
		}
		while (i < argc - 2)
			pipe_handler(argv[i++], envp);
		parent_handler(outfile, envp, argv, i);
	}
	else
		ft_error(4, NULL);
	return (0);
}
