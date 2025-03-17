/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:23:25 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 17:24:55 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// return zero if not operators, two if pipe, one if else operators
int	is_operator_fun(char *str)
{
	if (!str)
		return (0);
	if (!ft_strcmp(str, "|") || !ft_strcmp(str, ">") || !ft_strcmp(str, "<")
		|| !ft_strcmp(str, ">>") || !ft_strcmp(str, "<<"))
	{
		if (!ft_strcmp(str, "|"))
			return (2);
		else
			return (1);
	}
	return (0);
}

int	is_char_operator_fun(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}
