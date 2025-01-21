/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:04:06 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/01/21 19:08:03 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

char *readline_fun()
{
	char *line;
	
	line = readline ("Enter a line: ");
	add_history(line);
	return (line);
}