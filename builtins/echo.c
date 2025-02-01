/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:57:52 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/01/31 17:35:27 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

char	*echo_n_fun(char *str)
{
	if (!str)
		printf("%s", str);
}

char	*echo_with_line_fun(char *str)
{
	if (!str)
		printf("%s\n", str);
}