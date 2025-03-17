/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:17:59 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 18:18:35 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_qout_export(char **str, int len)
{
	int		i;
	int		j;
	char	*new_str;
	int		is_got_equal;

	new_str = malloc(sizeof(char) * (len + 3));
	if (!new_str)
		return ;
	i = -1;
	is_got_equal = 0;
	j = 0;
	while (str[0][++i])
	{
		new_str[j++] = str[0][i];
		if (is_got_equal == 0 && str[0][i] == '=')
		{
			new_str[j++] = '\"';
			is_got_equal = 1;
		}
	}
	if (is_got_equal == 1)
		new_str[j++] = '\"';
	new_str[j] = '\0';
	*str = free_string(str);
	*str = new_str;
}

char	**copy_array2d_export(char **array2d)
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
		new_array2d[i] = join_with_restore(&new_array2d[i], "declare -x ",
				array2d[i], NULL);
		ft_add_qout_export(&new_array2d[i], ft_strlen(new_array2d[i]));
		i++;
	}
	new_array2d[i] = NULL;
	return (new_array2d);
}
