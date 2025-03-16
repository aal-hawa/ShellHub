/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:52:54 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/16 23:20:27 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* free char **array2d by the size,
if size equal zero it will auto get size from the size_tarray2d
but if size not equal zero be sure that the last string of the array2d equal NULL*/
void	free_array2d(char ***dst, size_t i)
{
	
	if (!*dst)
		return ;

	if (i == 0)
		i = len_array2d(*dst);

	while (i > 0)
	{
		i--;
		if (dst[0][i])
		{
			free(dst[0][i]);
			dst[0][i] = NULL;
		}
	}
	free(*dst);
	*dst = NULL;
}
