/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:51:39 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/01/19 19:31:29 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell()
{
	while (1)
	{
		char *line;
		// char **tokens;
	
		line = readline_func();
		printf("the input: %s\n", line);
		// tokens = tokens_fun(line);
	}
}
