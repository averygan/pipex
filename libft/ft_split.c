/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:33:11 by agan              #+#    #+#             */
/*   Updated: 2023/09/07 17:11:06 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_freewords(char **s, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

static int	ft_wordcount(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c && s[i - 1] != c)
			count++;
		i++;
	}
	if (s[i] == '\0' && s[i - 1] != c && i != 0)
		count++;
	return (count);
}

static char	**ft_words(char **words, char const *s, char c, int wordcount)
{
	int	count;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < wordcount)
	{
		count = 0;
		while (s[j] && s[j] == c)
			j++;
		while (s[j] && s[j] != c)
		{
			count++;
			j++;
		}
		words[i] = ft_substr(s, j - count, count);
		if (!words[i])
		{
			ft_freewords(words, i);
			return (NULL);
		}
		i++;
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	int		wordcount;

	wordcount = ft_wordcount(s, c);
	words = malloc(sizeof(char *) * (wordcount + 1));
	if (!words)
		return (NULL);
	words[wordcount] = NULL;
	if (ft_words(words, s, c, wordcount))
		return (words);
	else
		return (NULL);
}
