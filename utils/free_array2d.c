/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:52:54 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/02/22 15:46:07 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* free char **array2d by the size,
if size equal zero it will auto get size from the size_tarray2d
but if size equal zero be sure that the last string of the array2d equal NULL*/
void	free_array2d(char **dst, size_t i)
{

	if (!dst)
		return ;
	if (i == 0)
		i = len_split(dst);
	while (i > 0)
	{
		i--;
		if (dst[i])
		{
			free(dst[i]);
			dst[i] = NULL;
		}
	}
	free(dst);
	dst = NULL;
}