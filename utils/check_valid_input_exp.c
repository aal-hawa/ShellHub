/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_input_exp.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:26:18 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 17:26:19 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_valid_alpha(char c)
{
	if (ft_isalpha(c) == 1 || c == '_')
		return (1);
	return (0);
}

int	check_is_valid_key(char *str)
{
	int	i;

	if (!str || str[0] == '\0' || !check_valid_alpha(str[0]))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(check_valid_alpha(str[i]) || ft_isdigit(str[i])))
			return (0);
		i++;
	}
	return (1);
}
