# include "../minishell.h"

void	execve_no_cmd(t_info *info)
{
	info->frs[info->i_childs] = fork();
	if (info->frs[info->i_childs] == 0)
	{
		close_fds_childs(info->fds, info);
		close(info->fds[info->i_childs][0]);
		close(info->fds[info->i_childs + 1][1]);
		exit_number(0, 0, info);
	}
	info->i_childs++;
}


void	do_execve_fun(t_token *token, t_info *info)
{
	if (!token)
		return ;
	info->frs[info->i_childs] = fork();
	if (info->frs[info->i_childs] == 0)
	{
		close_fds_childs(info->fds, info);
		childs(token, info);
	}
	info->fd_file_r = close_fd_fun(info->fd_file_r);
	info->i_childs++;
}

void	for_execve(t_token *token, t_info *info)
{
	if (token->is_bilt_cmd != 0)
	{
		do_execve_fun(token, info);
	}
}
