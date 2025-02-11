#include "../minishell.h"

void	init_info(int ac, char *env, char **envp, t_info *info)
{
	info->ac = ac;
	info->env = env;
	info->str_i = 0; //ac - 3
	info->envp = envp;
	info->is_bonus = 1;
	info->limiter = NULL;
	info->i_split = 0;
	info->path_commd = NULL;
	info->env_null = 0;
	info->is_for_w = 0;
	info->fd_file_w = -2;
	info->is_exit_one = 0;


	info->i_fds = 0;
	info->i_childs = 0;
	info->i_wait = 0;
	info->fd_file_r = -2;
	info->offset = 0;
	info->i_limiter = 0;
}

void	reset_info(t_info *info)
{
	info->str_i = 0;
	info->limiter = NULL; //
	info->i_split = 0; //
	info->env_null = 0; //
	info->is_for_w = 0;
	info->fd_file_w = -2;
	info->is_exit_one = 0;
}