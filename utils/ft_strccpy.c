<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:10:23 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/01/25 14:27:47 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
=======
>>>>>>> ac0aed6ef00dd035acd00089f5f54c89aeb33bcb

#include "../minishell.h"

// copy str to char
char *ft_strccpy(char *str, char to_char)
{
	char	*dest;
	size_t	i;

	i = ft_strclen(str, to_char);
	if (i == 0)
		return (NULL);
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
