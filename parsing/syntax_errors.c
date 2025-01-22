/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:54:33 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/01/22 20:06:52 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"


int	check_error_operators(char **tokens)
{
	int i;

	i = 0;
	while (tokens[i])
	{
		if (is_operator_fun(tokens[i]) == 1
			&& (!tokens[i + 1] || is_operator_fun(tokens[i + 1]) == 1))
			return(1);
		i++;
	}
	return (0);
}