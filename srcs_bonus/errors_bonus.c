/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:39:50 by agan              #+#    #+#             */
/*   Updated: 2023/10/24 20:39:51 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// Error handling for:
// Command not found, pipe, fork, redirection and invalid args error
void	ft_error(int num, char *cmd)
{
	if (num == 0)
	{
		ft_putstr_fd("pipex: line 1: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	if (num == 1)
	{
		ft_putstr_fd("error: unable to pipe\n", 2);
		exit(127);
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

// dup2 helper function for error handling
void	ft_dup(int to, int from)
{
	if (dup2(to, from) < 0)
		ft_error(3, NULL);
}
