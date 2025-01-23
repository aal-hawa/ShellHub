/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:05:08 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/01/23 15:26:52 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

// send str from first char after single qoutes
// return NULL if did not have second single qoutes
// return dest between the single qoutes
char *single_quot_fun(char *str)
{
		return (ft_strccpy(str,  '\''));
}
