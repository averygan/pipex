/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:28:04 by agan              #+#    #+#             */
/*   Updated: 2023/09/07 10:45:21 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (s[j])
	{
		if (s[j] == (unsigned char)c)
			i = j;
		j++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s + j);
	if (i != -1)
		return ((char *)s + i);
	else
		return (NULL);
}
