/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:54:21 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 18:07:41 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_name_herdoc_files(t_info *info)
{
	t_token	*token;
	int		index_files;
	char	*str;
	t_node	*input_node;

	if (info->index_files_crt == 0)
		return ;
	index_files = 0;
	token = info->tokens;
	while (token)
	{
		input_node = token->redirect;
		while (input_node)
		{
			if (!ft_strcmp(input_node->type_before, "<<"))
			{
				str = new_name_herdoc(index_files);
				index_files++;
				input_node->fd_name = str;
			}
			input_node = input_node->next;
		}
		token = token->next;
	}
}

void	open_here_doc(t_node *node, t_info *info)
{
	info->fd_file_r = close_fd_fun(info->fd_file_r);
	if (node->fd_name)
		info->fd_file_r = open_file_r(node->fd_name);
}

void	open_herdoc_files(char **herdoc_files, t_info *info)
{
	int	i;

	if (!herdoc_files)
		return ;
	i = 0;
	while (herdoc_files[i])
	{
		init_here_doc(herdoc_files[i], info);
		i++;
	}
}

char	*new_name_herdoc(int index)
{
	char	*str;
	char	*str_i;

	str_i = ft_itoa(index);
	str = ft_strjoin("/tmp/tmp_shell_", str_i);
	str_i = free_string(&str_i);
	return (str);
}

void	init_here_doc(char *herdoc_file, t_info *info)
{
	char	*str;

	info->fd_file_r = close_fd_fun(info->fd_file_r);
	str = new_name_herdoc(info->index_files_crt);
	info->index_files_crt++;
	info->fd_file_r = open_file_r_w(str);
	info->limiter = ft_strjoin(herdoc_file, "\n");
	info->i_limiter = ft_strlen(info->limiter);
	ft_putstr_fd_malloc(get_next_line(info), info->fd_file_r, 1);
	info->fd_file_r = close_fd_fun(info->fd_file_r);
	str = free_string(&str);
}
