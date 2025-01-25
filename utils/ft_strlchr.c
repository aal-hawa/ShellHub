/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:06:25 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/01/25 17:08:06 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

char	*ft_strlchr(char **str, char lst_char, int is_str_malloc)
{
	size_t	i;
	char	*dest;

	i = ft_strlen(*str);
	while (1)
	{
		if (str[0][i] == lst_char)
			break ;
		if (i == 0)
			break ;
		i--;
	}
	if (i == 0)
		return (*str);
	dest = malloc(sizeof(char) * i);
	if (!dest)
		return (free_fun(str), NULL);
	ft_strlcpy(dest, *str, i);
	if (is_str_malloc == 1)
		free_fun(str);
	return (dest);
}