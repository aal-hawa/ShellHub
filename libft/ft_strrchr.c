/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:53:45 by tmahmoud          #+#    #+#             */
/*   Updated: 2024/07/17 02:25:03 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	if (!s)
		return (NULL);
	if ((unsigned char)c == '\0')
		return ((char *)(s + i));
	while (i >= 0)
	{
		if ((unsigned char) c == s[i])
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}
