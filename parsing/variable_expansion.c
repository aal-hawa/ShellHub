/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:54:05 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/01/22 17:48:44 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

char	*value_fun(char *str, char devide_char)
{
	int	i;
	int	y;
	char	*dest;

	i = 0;
	while (str[i] && str[i] != devide_char)
		i++;
	if (!str[i] || !str[i + 1])
		return (NULL);
	i++;
	y = ft_strlen(&str[i]);
	dest = malloc(sizeof(char) * (y + 1));
	if (!dest)
		return (NULL);
	y = 0;
	while (str[i])
		dest[y++] = str[i++];
	dest[y] = '\0';
	return (dest);
}

char *varible_fun(char *str, char devide_char)
{
	int	i;
	char	*dest;

	i = 0;
	while (str[i] && str[i] != devide_char)
		i++;
	if (!str[i])
		return (NULL);
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != devide_char)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*doller_sign_fun(char *str, t_info *info)
{
	int	i;
	char	*varible;

	i = 0;
	while (info->env[i])
	{
		varible = varible_fun(info->env[i], '=');
		if (!varible)
		{
			i++;
			continue ;
		}
		if (varible == str)
			return (value_fun(info->env[i], '='));
		free (varible);
		varible = NULL;
		i++;
	}
	return (NULL);
}
