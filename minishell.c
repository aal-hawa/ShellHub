/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:51:39 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/01/19 19:15:05 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell()
{
	while  (1)
	{
		char *line;
		char **tokens;
	
		line = readline_func();
		printf("the input: %s\n", line);
		tokens = tokens_fun(line);
	}

	
}