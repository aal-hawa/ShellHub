
#include "../minishell.h"

int	is_exist_str_in_2array(char **array2d, char *del_str, int size_str)
{
	int	i;

	i = 0;
	while (array2d[i])
	{
		if ((size_str == 0 && !ft_strcmp(array2d[i], del_str))
			|| (size_str != 0 && !ft_strncmp(array2d[i], del_str, size_str)))
			return (1);
		i++;
	}
	return (0);
}
int	len_split(char **split)
{
	int	len;

	len = 0;
	if (!split)
		return (len);
	while (split[len])
		len++;
	return (len);
}
char	**copy_split(char **split)
{
	int	i;
	int	len;
	char	**new_split;

	i = 0;
	if (!split)
		return (NULL);
	len = len_split(split);
	new_split = malloc(sizeof(char *) * (len + 1));
	if (!new_split)
		return (NULL);
	while (i < len)
	{
		new_split[i] = ft_strdup(split[i]);
		i++;
	}
	new_split[i] = NULL;
	return (new_split);
}

// check if you want share adress of split three pointers
char	**del_str_from_array2d(char **array2d, char *del_str, int size_str)
{
	int		i;
	int		y;
	int		len;
	char	**new_split;

	if (!is_exist_str_in_2array(array2d, del_str, size_str))
		return (array2d); 
	i = -1;
	y = -1;
	len = len_split(array2d);
	new_split = malloc(sizeof(char *) * (len));
	if (!new_split)
		return (NULL);
	while (array2d[++i])
	{
		if ((size_str == 0 && !ft_strcmp(array2d[i], del_str))
			|| (size_str != 0 && !ft_strncmp(array2d[i], del_str, size_str)))
		{
			new_split[++y] = ft_strdup(array2d[i]);
			if (!new_split[y])
				return (free_split(new_split, y - 1), NULL);
		}
	}
	new_split[++y] = NULL;
	return (free_split(array2d, len), new_split);
}

char	**add_in_split(char **split, char *add_str, int is_alpha)
{
	int		i;
	int		j;
	int		len;
	char	**new_split;

	i = 0;
	j = 0;
	len = len_split(split) + 1;
	new_split = malloc(sizeof(char *) * (len + 1));
	if (!new_split)
		return (NULL);
	while (split[i])
	{
		if (is_alpha == 1 && ft_strcmp(split[i], add_str) > 0 && is_alpha++)
			new_split[j] = ft_strdup(add_str);
		else
			new_split[j] = ft_strdup(split[i++]);
		if (!new_split[j++])
			return(free_split(new_split, j - 2), NULL);
	}
	if (is_alpha < 2)
		new_split[j++] = ft_strdup(add_str);
	new_split[j] = NULL;
	free_split(split, len - 1);
	return (new_split);
}

char	**marge_2_splits(char **first_split, char **second_split)
{
	int		i;
	int		j;
	int		len1;
	int		len2;
	char	**new_split;

	i = 0;
	len1 = len_split(first_split);
	len2 = len_split(second_split);
	new_split = malloc(sizeof(char *) * (len1 + len2 + 1));
	if (!new_split)
		return (NULL);
		
	while (first_split && first_split[i])
	{
		new_split[i] = ft_strdup(first_split[i]);
		if (!new_split[i])
			return(free_split(new_split, i - 1), NULL);
		i++;
	}
	j = 0;
	while (second_split && second_split[j])
	{
		new_split[i] = ft_strdup(second_split[j]);
		if (!new_split[i])
			return(free_split(new_split, i - 1), NULL);
		i++;
		j++;
	}
	new_split[i] = NULL;
	free_split(first_split, len1);
	free_split(second_split, len2);
	return (new_split);
}
