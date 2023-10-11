/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:23:47 by agan              #+#    #+#             */
/*   Updated: 2023/09/07 10:42:06 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*des;
	char	*s;
	size_t	i;

	des = (char *)dest;
	s = (char *)src;
	i = 0;
	while (&des[i] != &s[i] && i < n)
	{
		des[i] = s[i];
		i++;
	}
	return (dest);
}
