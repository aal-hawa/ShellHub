/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_array2d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:27:36 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 17:27:37 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_array2d(char **array2d, int is_with_newline)
{
	int	i;

	i = 0;
	if (!array2d)
		return ;
	while (array2d[i])
	{
		if (is_with_newline == 1)
			printf("%s\n", array2d[i++]);
		else
			printf("%s ", array2d[i++]);
	}
}

void	print_array2d_fd(char **array2d, int fd)
{
	int	i;

	i = 0;
	if (!array2d)
		return ;
	while (array2d[i])
		ft_putstr_fd(array2d[i++], fd);
}
