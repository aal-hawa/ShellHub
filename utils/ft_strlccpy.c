/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlccpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:11:28 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 18:13:37 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// copy char *str from devide_char to last char
// if didnt have the char devide_char inside the char *str it will return NULL
// if have it will return malloc char	*
char	*ft_strlccpy(char *str, char devide_char)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != devide_char)
		i++;
	if (!str[i] || !str[i + 1])
		return (NULL);
	i++;
	return (ft_strdup(&str[i]));
}
