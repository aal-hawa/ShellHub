
#include "../minishell.h"

void	free_split(char **split, int len)
{
	int i;

	i = 0;
	while (i < len)
		free(split[i]);
	free (split);
}

int	len_split(char **split)
{
	int	len;

	len = 0;
	while (split[len])
		len++;
	return (len);
}
// check if you want share adress of split three pointers
char **del_from_split(char **split, char *del_str)
{
	int	i;
	int	y;
	int	len;
	char	**new_split;

	i = 0;
	y = 0;
	len = len_split(split);
	new_split = malloc(sizeof(char *) * (len));
	if (!new_split)
		return (NULL);
	while (split[i])
	{
		if (!ft_memcmp(split[i], del_str, ft_strlen(del_str)))
		{
			new_split[y] = ft_strdup(split[i]);
			if (!new_split[y])
				return(free_split(new_split, y - 1), NULL);
			y++;
		}
		i++;
	}
	new_split[y] = NULL;
	free_split(split, len - 1);
	return (new_split);
}

char **add_in_split(char **split, char *add_str)
{
	int	i;
	int	len;
	char	**new_split;

	i = 0;
	len = len_split(split);
	len++;
	new_split = malloc(sizeof(char *) * (len + 1));
	if (!new_split)
		return (NULL);
	while (split[i])
	{
		new_split[i] = ft_strdup(split[i]);
		if (!new_split[i])
			return(free_split(new_split, i - 1), NULL);
		i++;
	}
	new_split[i] = ft_strdup(add_str);
	new_split[i++] = NULL;
	free_split(split, len - 1);
	return (new_split);
}
