/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:07:30 by agan              #+#    #+#             */
/*   Updated: 2023/09/07 10:42:22 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*des;
	char	*s;
	size_t	i;

	des = (char *)dest;
	s = (char *)src;
	i = 0;
	if (!des && !s)
		return (NULL);
	if (des > s)
	{
		while (n-- > 0)
			des[n] = s[n];
	}
	else
	{
		while (i < n)
		{
			des[i] = s[i];
			i++;
		}
	}
	return (dest);
}
