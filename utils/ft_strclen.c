/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:13:39 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/01/25 14:24:40 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// return length of string before to_char
// return 0 if did not have to_char inside the string
size_t	ft_strclen(const char *s, char to_char)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != to_char)
		i++;
	if (!s[i])
		return (0);
	return (i);
}