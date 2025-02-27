/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:08:13 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/02/27 21:13:52 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

char	*status_program_fun(char **str, t_info *info)
{
	char	*str_itoa;
	char	*str_join;
	
	str_itoa = ft_itoa(info->status_exit);
	str_join = ft_strjoin(str_itoa, &str[0][1]);
	str_itoa = free_string(&str_itoa);
	*str = free_string(str);
	*str = str_join;
	return (str_join);
}
