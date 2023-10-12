/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:26:04 by agan              #+#    #+#             */
/*   Updated: 2023/10/11 15:26:06 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Helper function to join path with command
char	*ft_shellpath(char *command)
{
	char	*res;

	res = ft_strjoin("/bin/", command);
	return (res);
}

// Print error if errno < 0
void	ft_error(int error)
{
	if (error != 0)
	{
		perror(NULL);
		exit(errno);
	}
}
