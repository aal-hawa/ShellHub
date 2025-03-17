/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:27:00 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 17:29:31 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// copy char *str to first char of char to_char
// if didnt have the char to_char inside the char *str it will return NULL
// if have it will return malloc char	*
char	*ft_strccpy(char *str, char to_char)
{
	char	*dest;
	ssize_t	i;

	if (!str)
		return (NULL);
	i = ft_strclen(str, to_char);
	if (i == 0)
		return (NULL);
	if (i == -1)
		return (ft_strdup(""));
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != to_char)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
