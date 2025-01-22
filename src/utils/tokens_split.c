/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:34:52 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/01/22 19:15:11 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	mymalloc(char **result, int i, size_t len)
{
	int	j;

	j = 0;
	result[i] = ft_calloc(len, 1);
	if (!result[i])
	{
		while (j < i)
			free(result[j++]);
		free(result);
		return (1);
	}
	return (0);
}

// static int check_valid(char const *s, char *str)
// {
// 	size_t	j;

// 	j = 0;
// 	new = 0;
// 	while (s[i] == c && s[i])
// 		i++;
// 	while (s[i] != c && s[i])
// 	{
// 		if (new == 0)
// 		{
// 			++words;
// 			new = 1;
// 		}
// 		i++;
// 	}
// }

int	fill(char **result, char const *s, char c)
{
	int		i;
	size_t	len;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s == c && *s)
			++s;
		while (*s != c && *s)
		{
			len++;
			++s;
		}
		if (len)
		{
			if (mymalloc(result, i, len + 1))
				return (1);
		}
		ft_strlcpy(result[i], s - len, len + 1);
		i++;
	}
	return (0);
}

size_t	wordscount(char const *s, char c)
{
	size_t	words;
	size_t	i;
	size_t	new;

	i = 0;
	words = 0;
	new = 0;
	while (s[i])
	{
		new = 0;
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			if (new == 0)
			{
				++words;
				new = 1;
			}
			i++;
		}
	}
	return (words);
}

char	**tokens_split(char const *s, char *str)
{
	size_t	words;
	char	**result;

	if (!s)
		return (NULL);
	words = 0;
	words = wordscount(s, str);
	result = ft_calloc((words + 1), sizeof(char *));
	if (!result)
		return (NULL);
	result[words] = NULL;
	if (fill(result, s, str))
		return (NULL);
	return (result);
}
