/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:50:36 by agan              #+#    #+#             */
/*   Updated: 2023/10/17 16:50:37 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// Free char **arr
void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

// Function to get all possible paths, split into array of paths
char	**ft_getenv(char **env)
{
	int		i;
	char	**allpath;
	char	*path;

	i = -1;
	if (!*env)
	{
		path = "/bin:/usr/bin:/usr/local/bin";
		allpath = ft_split(path, ':');
		return (allpath);
	}
	while (env[++i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			allpath = ft_split(&env[i][5], ':');
			return (allpath);
		}
	}
	return (NULL);
}

// strjoin from char **allpath to get executable path
char	*ft_getpath(char **allpath, char *cmd)
{
	int		i;
	char	*tmp_path;
	char	*path;

	i = 0;
	while (allpath[i])
	{
		tmp_path = ft_strjoin(allpath[i], "/");
		path = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (access(path, X_OK) == 0)
		{
			ft_free(allpath);
			allpath = NULL;
			return (path);
		}
		free(path);
		i++;
	}
	ft_free(allpath);
	return (cmd);
}
