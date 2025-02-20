#include "libft.h"
#include <stdio.h>

int	is_qout_fun(int last_is_qout, char c)
{
	if (last_is_qout == 0 && (c == '\"' || c == '\''))
		last_is_qout = 1;
	if (last_is_qout == 1 && (c == '\"' || c == '\''))
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
			is_qout = is_qout_fun(is_qout, *s);
			len++;
			++s;
		}
		if (len)
		{
			if (mymalloc(result, i, len + 1))
				return (1);
		}
		ft_strlcpy(result[i], s - len, len + 1);
		printf("result[i] %s\n", result[i]);
		i++;
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
			// "a ll"
		while ((s[i] != c || is_qout != 0) && s[i])
		{
			if (new == 0)
			{
				++words;
				new = 1;
			}
			is_qout = is_qout_fun(is_qout, s[i]);
			i++;
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
	printf("---------this split---------\n");
	if (fill(result, s, c))
		return (NULL);
	printf("---------finish split---------\n");
	return (result);
}
