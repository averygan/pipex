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
	char	*quote_end;
	int	i;

	token_count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote_end = ft_strrchr(&s[i], s[i]);
			if (quote_end)
			{
				i = s - quote_end;
				token_count++;
			}
		}
		else if (s[i] != c && (s[i + 1] == '\0' || s[i + 1] == ' '))
			token_count++;
		i++;
	}
	return (token_count);
}

void	alloc_words(char **words, char *s, char c)
{
	int 	count;
	char	*quote_end;
	int	i;
	int	j;

	i = -1;
	j = 0;
	count = 0;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote_end = ft_strrchr(&s[i], s[i]);
			words[j++] = ft_substr(&s[i], 1, quote_end - &s[i] - 1);
			i = quote_end - s;
		}
		else if (s[i] != c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		else if (s[i] != c && (s[i + 1] == '\0' || s[i + 1] == c))
		{
			count++;
			words[j++] = ft_substr(s, i - count + 1, count);
			count = 0;
		}
	}
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
	alloc_words(words, s, c);
	if (words)
		return (words);
	else
		return (NULL);
}