/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:19:20 by agan              #+#    #+#             */
/*   Updated: 2023/09/07 12:33:17 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*sub;
	size_t		i;
	size_t		slen;

	slen = (unsigned int)ft_strlen(s);
	i = -1;
	if (start >= slen)
	{
		sub = malloc(sizeof(char));
		if (sub == NULL)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	if (slen - start > len)
		sub = malloc(sizeof(char) * len + 1);
	else
		sub = malloc(sizeof(char) * (slen - start) + 1);
	if (sub == NULL)
		return (NULL);
	while (s[start + ++i] && i < len)
		sub[i] = s[start + i];
	sub[i] = '\0';
	return (sub);
}
