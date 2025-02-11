
#include "../minishell.h"

int	is_exit_str_in_split(char **split, char *del_str)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (!ft_strcmp(split[i], del_str))
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
char **del_from_split(char **split, char *del_str)
{
	int		i;
	int		y;
	int		len;
	char	**new_split;

	i = 0;
	y = 0;
	if (!is_exit_str_in_split(split, del_str))
		return (split); 
	len = len_split(split);
	new_split = malloc(sizeof(char *) * (len));
	if (!new_split)
		return (NULL);
	while (split[i])
	{
		if (!ft_strcmp(split[i], del_str))
		{
			new_split[y] = ft_strdup(split[i]);
			if (!new_split[y])
				return(free_split(new_split, y - 1), NULL);
			y++;
		}
		i++;
	}
	return (new_split[y] = NULL, free_split(split, len), new_split);
}

char **add_in_split(char **split, char *add_str, int is_alpha)
{
	int	i;
	int	len;
	char	**new_split;

	i = 0;
	len = len_split(split);
	len++;
	new_split = malloc(sizeof(char *) * (len + 1));
	if (is_alpha == 1)
		is_alpha++;
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
char	**marge_2_splits(char **first_split, char **second_split)
{
	int	i;
	int	j;
	int	len1;
	int	len2;
	char	**new_split;

	printf("1-----------\n");

	i = 0;
	len1 = len_split(first_split);
	len2 = len_split(second_split);
	printf("len1: %d\n", len1);
	printf("len2: %d\n", len2);

	new_split = malloc(sizeof(char *) * (len1 + len2 + 1));
	printf("2-----------\n");


	if (!new_split)
		return (NULL);
		
	while (first_split && first_split[i])
	{
		new_split[i] = ft_strdup(first_split[i]);
		printf("new_split[i]: %s\n", new_split[i]);
		if (!new_split[i])
			return(free_split(new_split, i - 1), NULL);
		i++;
	}
	printf("3-----------\n");

	j = 0;
	while (second_split && second_split[j])
	{
		new_split[i] = ft_strdup(second_split[j]);
		printf("new_split[i]: %s\n", new_split[i]);

		if (!new_split[i])
			return(free_split(new_split, i - 1), NULL);
		i++;
		j++;
	}
	new_split[i] = NULL;
	printf("4-----------\n");
	printf("len1: %d\n", len1);

	free_split(first_split, len1);
	printf("5-----------\n");
	printf("len2: %d\n", len2);

	free_split(second_split, len2);
	printf("6-----------\n");

	return (new_split);
}
