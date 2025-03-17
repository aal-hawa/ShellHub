/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:23:36 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 17:23:39 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// send char *str from first char after single qoutes
// return NULL if did not have second single qoutes
// return malloc char * between the single qoutes
char	*single_quot_fun(char *str)
{
	if (!str)
		return (NULL);
	return (ft_strccpy(str, '\''));
}
