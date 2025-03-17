/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restore_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:27:51 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 18:16:40 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_restore_value(char **dest, char **str, int is_str_malloc)
{
	if (!str || !*str)
		return (*dest);
	*dest = free_string(dest);
	*dest = ft_strdup(*str);
	if (!*dest)
		return (NULL);
	if (is_str_malloc == 1)
		*str = free_string(str);
	return (*dest);
}

char	*join_with_restore(char **dst, char *s1, char *s2, char *s3)
{
	char	*str_join;

	str_join = ft_strjoin(s1, s2);
	*dst = ft_restore_value(dst, &str_join, 1);
	if (s3)
	{
		str_join = ft_strjoin(*dst, s3);
		*dst = ft_restore_value(dst, &str_join, 1);
	}
	return (*dst);
}
