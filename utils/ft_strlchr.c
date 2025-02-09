/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:06:25 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/02/09 19:32:40 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

// return str to the last char inside it
// example: folder1/folder2/folder3 by char is / it will return folder1/folder2
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
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (free_fun(str), NULL);
	ft_strlcpy(dest, *str, i + 1);
	if (is_str_malloc == 1)
		free_fun(str);
	return (dest);
}
