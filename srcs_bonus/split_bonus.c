/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:58:08 by agan              #+#    #+#             */
/*   Updated: 2023/10/17 16:58:09 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	token_count(char *s, char c)
{
	int	token_count;
	int	flag;
	int	i;

	token_count = 0;
	flag = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '"') && !flag)
			flag = !flag;
		else if ((s[i] == '\'' || s[i] == '"') && flag)
			flag = 0;
		if (s[i] != c && (s[i + 1] == '\0' || s[i + 1] == ' ') && !flag)
			token_count++;
		i++;
	}
	return (token_count);
}

char	**alloc_words(char **words, char *s, char c, int word_count)
{
	int	letters_count;
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (++j < word_count)
	{
		letters_count = 0;
		c = ' ';
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			if (s[i] == '\'' || s[i] == '"')
				c = s[i++];
			i++;
			letters_count++;
		}
		words[j] = ft_substr(s, i - letters_count, letters_count);
		if (s[i] && (s[i] == '\'' || s[i] == '"'))
			i++;
	}
	return (words);
}

char	**arr_split(char *s, char c)
{
	char	**words;
	int		word_count;

	word_count = token_count(s, c);
	words = malloc(sizeof(char *) * (word_count + 1));
	if (!words)
		return (NULL);
	words[word_count] = NULL;
	if (alloc_words(words, s, c, word_count))
		return (words);
	else
		return (NULL);
}
