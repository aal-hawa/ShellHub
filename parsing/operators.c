/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:06:56 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/01/22 20:07:13 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	is_operator_fun(char *str)
{
	if (ft_memcmp(str, "|", 1) || ft_memcmp(str, ">", 1)
		|| ft_memcmp(str, "<", 1)
		|| ft_memcmp(str, ">>", 2) || ft_memcmp(str, "<<", 2))
		return (1);
	return (0);
}