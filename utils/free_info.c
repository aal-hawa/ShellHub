
#include "../minishell.h"

void	free_info(t_info *info)
{
	free_array2d(&info->envp, 0);
	free_array2d(&info->export, 0);
	info->limiter = free_string(&info->limiter);
}