/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:50:19 by agan              #+#    #+#             */
/*   Updated: 2023/10/16 14:50:24 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	**alloc_words(char **words, char *s, char c)
{
	int 	count;
	char	*quote_end;
	int	i;
	int	j;

	i = 0;
	j = 0;
	count = 0;
	while (s[i])
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
	if (alloc_words(words, s, c))
		return (words);
	else
		return (NULL);
}

// int	main(void)
// {
// 	char *s = "awk ''{count++} END {print count}''";
// 	char **words;

// 	words = arr_split(s, ' ');
// 	int i = 0;
// 	while (words[i])
// 	{
// 		printf("%s\n", words[i]);
// 		i++;
// 	}
// }
