/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:11:38 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/01/22 20:15:41 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int init_info(char **envp,t_info *info)
{
	info->env = envp;
	info->status_exit = 0;
	info->curent_path = NULL;
}
