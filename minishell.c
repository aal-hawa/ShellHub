/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:51:39 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/01/25 17:16:48 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// ls | grep "txt"
void	minishell(void)
{
	char	*line;
	char **tokens;

	while (1)
	{
		// char **tokens;
		// readLine && hestory
		line = readline_fun();
		printf("the input: %s\n", line);
		tokens = tokens_fun(line);
		while(*tokens)
			printf("the tokens: %s\n", *tokens++);
		free(line);
		// nodes
		// syntax error
		// commands structure
	}
}
