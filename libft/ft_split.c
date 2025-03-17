/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 22:04:01 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/03/17 17:19:24 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_qout_fun1(int last_is_qout, char c)
{
	if (last_is_qout == 0 && c == '\'')
		last_is_qout = 1;
	else if (last_is_qout == 0 && c == '\"')
		last_is_qout = 2;
	else if (last_is_qout == 1 && c == '\'')
		last_is_qout = 0;
	else if (last_is_qout == 2 && c == '\"')
		last_is_qout = 0;
	return (last_is_qout);
}

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

int	fill(char **result, char const *s, char c)
{
	int		i;
	size_t	len;
	int		is_qout;

	i = 0;
	is_qout = 0;
	while (*s)
	{
		len = 0;
		while (*s == c && *s)
			++s;
		while ((*s != c || is_qout != 0) && *s)
		{
			is_qout = is_qout_fun1(is_qout, *s);
			len++;
			++s;
		}
		if (len)
		{
			if (mymalloc(result, i, len + 1))
				return (1);
		}
		ft_strlcpy(result[i++], s - len, len + 1);
	}
	return (0);
}

size_t	wordscount(char const *s, char c)
{
	size_t	words;
	size_t	i;
	size_t	new;
	int		is_qout;

	i = 0;
	words = 0;
	new = 0;
	is_qout = 0;
	while (s[i])
	{
		new = 0;
		while (s[i] == c && s[i])
			i++;
		while ((s[i] != c || is_qout != 0) && s[i])
		{
			if (new == 0)
			{
				++words;
				new = 1;
			}
			is_qout = is_qout_fun1(is_qout, s[i++]);
		}
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**result;

	if (!s)
		return (NULL);
	words = 0;
	words = wordscount(s, c);
	result = ft_calloc((words + 1), sizeof(char *));
	if (!result)
		return (NULL);
	result[words] = NULL;
	if (fill(result, s, c))
		return (NULL);
	return (result);
}
