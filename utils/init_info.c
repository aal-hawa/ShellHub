#include "../minishell.h"

void	init_info(char **envp, t_info *info)
{
	info->str_i = 0;
	info->envp = copy_array2d(envp);
	info->export = copy_array2d_export(envp);
	info->limiter = NULL;
	info->path_commd = NULL;
	info->fd_file_w = -2;
	info->i_fds = 0;
	info->i_childs = 0;
	info->i_wait = 0;
	info->fd_file_r = -2;
	info->i_limiter = 0;
	info->status_exit = 0;
	info->curent_path = NULL;
	info->index_files_crt = 0;
	info->fds = NULL;
	info->frs = NULL;
	info->herdoc_files = NULL;
	info->tokens = NULL;
}

void	reset_info(t_info *info)
{
	info->str_i = 0;
	info->limiter = free_string(&info->limiter);
	info->fd_file_w = close_fd_fun(info->fd_file_w);
	info->fd_file_r = close_fd_fun(info->fd_file_r);
	info->i_fds = 0;
	if (info->herdoc_files)
		free_array2d(&info->herdoc_files, 0);
	free_tokens(&info->tokens);
}
