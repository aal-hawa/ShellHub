/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:09:52 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/01/22 17:25:45 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

char **tokens_fun(char *line)
{
	char **split;
	split = ft_split(line, ' ');
	// sub split if i have (< << > >> |) in side each split[i]
	return (split);	
}