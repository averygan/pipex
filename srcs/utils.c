/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:46:22 by agan              #+#    #+#             */
/*   Updated: 2023/10/13 15:46:25 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Error handling for command not found, pipe, fork and invalid args
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
		ft_putstr_fd("invalid argument: ./pipex file1 cmd1 cmd2 file2\n", 2);
}

// Function to handle redirection and erorr handling
void	ft_redirect(int *in, int *out)
{
	if (dup2(*in, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("error: dup2\n", 2);
		exit(9);
	}
	if (dup2(*out, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("error: dup2\n", 2);
		exit(9);
	}
}

// Open files and check for errors
int	ft_openfiles(char **argv, int num)
{
	int	fd;

	if (num == 0)
		fd = open(argv[1], O_RDONLY);
	if (num == 1)
		fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("error: unable to open file", 2);
		exit(errno);
	}
	return (fd);
}
