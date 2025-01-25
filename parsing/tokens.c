/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:09:52 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/01/25 15:57:43 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

char **tokens_fun(char *line)
{
	line = pre_split(&line, "|<>");
	char **split;
	split = ft_split(line, ' ');
	return (split);	
}