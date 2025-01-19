/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:26:34 by tmahmoud          #+#    #+#             */
/*   Updated: 2024/07/17 13:53:21 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (count && size && count > (SIZE_MAX / size))
		return (NULL);
	p = malloc(count * size);
	if (p == NULL)
		return (p);
	ft_bzero(p, count * size);
	return (p);
}
