/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:22:10 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/19 03:57:40 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*free_string(char **this_string)
{
	if (!this_string || !*this_string)
		return (NULL);
	free(*this_string);
	*this_string = NULL;
	return (NULL);
}

char	*get_next_line(t_info *info)
{
	char	*text_buffer;
	char	*returntext;
	int		is_done;

	g_global_variable = 0;
	is_done = 0;
	text_buffer = NULL;
	while (1)
	{
		returntext = readline("> ");
		if (!returntext)
			break ;
		if (g_global_variable == 1)
			break ;
		text_buffer = strjoin_herdoc(&text_buffer, returntext, &is_done, info);
		returntext = free_string(&returntext);
		if (is_done == 1)
			break ;
	}
	return (text_buffer);
}
