# include "../minishell.h"

void	str_i_count(t_info *info)
{
	t_token	*token;

	token = info->tokens;
	while (token)
	{
		if (token->next)
			info->str_i++;
		token = token->next;
	}
	if (info->str_i > 0)
		info->str_i++;
	else if (info->str_i == 0)
	{
		token = info->tokens;
		if (token->is_bilt_cmd == 1)
			info->str_i++;
	}
	printf ("info->str_i: %d\n", info->str_i);
}
void	do_builtins_check_fork(t_token *token,  t_info *info, char ***result_blts)
{
	pid_t	frs_1;
	if (info->str_i > 0)
	{
		frs_1 = fork();
		if (frs_1 == 0)
		{
			if (do_builtins(token, result_blts, info) == 1)
			{
				dup2(info->fds[info->i_childs + 1][1], STDOUT_FILENO);
				print_array2d_fd(*result_blts, STDOUT_FILENO);
			}
			close_fds_childs(info->fds, info);
			close(info->fds[info->i_childs + 1][1]);
			close(info->fds[info->i_childs][0]);
			if (info->str_i > 0)
				de_allocate(&info->fds, &info->frs, info->str_i);
			free_array2d(result_blts, 0);
			exit_number(info->status_exit, info);
		}
		info->fd_file_w = close_fd_fun(info->fd_file_w);
		info->i_childs++;
	}
	else
		do_builtins(token, result_blts, info);
}

int open_all_files(t_node *node, t_info *info)
{
	t_node	*this_node;

	this_node = node;
	while (this_node)
	{
		if(direct_fun(this_node, info) == 1)
			return (1);
		this_node = this_node->next;
	}
	return (0);
}

int	check_open_files(t_token *token, t_info *info)
{
	int		is_exit;
	
	info->fd_file_r = close_fd_fun(info->fd_file_r);
	info->fd_file_w = close_fd_fun(info->fd_file_w);
	is_exit = 0;
	is_exit = open_all_files(token->input_redirect, info);
	if (is_exit == 0)
		is_exit = open_all_files(token->output_redirect, info);
	if (is_exit == 1)
	{
		info->i_childs++;
		return (1);
	}
	return (0);
}

void	dir_blt_execve_fun(t_token *tokens, t_info *info)
{
	char	**result_blts;

	result_blts = NULL;
	info->i_childs = 0;
	if (info->fd_file_r == -1)
		info->i_childs = 1;
	while (tokens)
	{
		if (check_open_files(tokens, info) == 1)
		{
			tokens = tokens->next;
			continue ;
		}
		if (tokens->cmd)
		{
			if (tokens->is_bilt_cmd == 0)
				do_builtins_check_fork(tokens, info, &result_blts);
			else
				for_execve(tokens, info);
		}
		tokens = tokens->next;
	}
	if (result_blts)
		free_array2d(&result_blts, 0);
}

void	put_name_herdoc_files(t_info *info)
{
	t_token *token;
	int		index_files;
	char 	*str;
	t_node *input_node;

	if (info->index_files_crt == 0)
		return ;
	index_files = 0;
	token = info->tokens;
	while (token)
	{
		input_node = token->input_redirect;
		while (input_node)
		{
			if (ft_strcmp(input_node->type_before, "<<"))
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

void	open_herdoc_files(char	**herdoc_files, t_info *info)
{
	int	i;

	if (!herdoc_files)
		return;
	i = 0;
	while (herdoc_files[i])
	{
		init_here_doc(herdoc_files[i], info);
		i++;
	}
}

int	execute_fun(t_info *info)
{
	int		**fds;
	pid_t	*frs;

	fds = NULL;
	frs = NULL;
	str_i_count(info);
	if (info->str_i > 0)
	{
		allocate_fds(&fds, &frs, info->str_i);
		info->fds = fds;
		info->frs = frs;
		info->i_fds = 0;
		while (info->i_fds < info->str_i + 1)
		{
			if (pipe(fds[info->i_fds++]) == -1)
			{
				error_pipe(fds, --info->i_fds, info);
				de_allocate(&fds, &frs, info->str_i);
				exit_number(1, info);
				return (1);
			}
		}
	}
	pwd_fun(info, -1);
	open_herdoc_files(info->herdoc_files, info);
	put_name_herdoc_files(info);
	dir_blt_execve_fun(info->tokens, info);
	return (finish_parent(info));
}
