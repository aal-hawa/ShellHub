/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:26:42 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 18:19:53 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_exist_str_in_2array(char **array2d, char *str)
{
	int	i;

	i = -1;
	while (array2d && array2d[++i])
	{
		if (!ft_strccmp(array2d[i], str, '='))
			return (i);
	}
	return (-1);
}

int	len_array2d(char **array2d)
{
	int	len;

	len = 0;
	if (!array2d)
		return (len);
	while (array2d[len])
		len++;
	return (len);
}

char	**copy_array2d(char **array2d, int is_newline)
{
	int		i;
	int		len;
	char	**new_array2d;

	i = 0;
	if (!array2d)
		return (NULL);
	len = len_array2d(array2d);
	new_array2d = malloc(sizeof(char *) * (len + 1));
	if (!new_array2d)
		return (NULL);
	while (i < len)
	{
		new_array2d[i] = NULL;
		if (!is_newline)
			new_array2d[i] = ft_strdup(array2d[i]);
		else
			new_array2d[i] = join_with_restore(&new_array2d[i], array2d[i],
					"\n", NULL);
		i++;
	}
	new_array2d[i] = NULL;
	return (new_array2d);
}

// check if you want share adress of split three pointers
char	**del_str_from_array2d(char ***array2d, char *del_str)
{
	int		i;
	int		y;
	int		len;
	char	**new_array2d;
	int		z;

	z = is_exist_str_in_2array(*array2d, del_str);
	if (z == -1)
		return (*array2d);
	i = -1;
	y = -1;
	len = len_array2d(*array2d);
	new_array2d = malloc(sizeof(char *) * (len));
	if (!new_array2d)
		return (NULL);
	while (array2d[0][++i])
	{
		if (i != z)
			new_array2d[++y] = ft_strdup(array2d[0][i]);
	}
	new_array2d[++y] = NULL;
	free_array2d(array2d, len);
	return (new_array2d);
}

char	**add_in_array2d(char ***array2d, char *add_str, int is_alpha)
{
	int		i;
	int		j;
	int		len;
	char	**new_array2d;

	i = 0;
	j = 0;
	len = len_array2d(*array2d) + 1;
	new_array2d = malloc(sizeof(char *) * (len + 1));
	if (!new_array2d)
		return (NULL);
	while (*array2d && array2d[0][i])
	{
		if (is_alpha == 1 && ft_strcmp(array2d[0][i], add_str) && is_alpha++)
			new_array2d[j++] = ft_strdup(add_str);
		else
			new_array2d[j++] = ft_strdup(array2d[0][i++]);
	}
	if (!*array2d || is_alpha < 2)
		new_array2d[j++] = ft_strdup(add_str);
	new_array2d[j] = NULL;
	free_array2d(array2d, len - 1);
	return (new_array2d);
}
