
# include "../minishell.h"

int	unset_func(char *name, t_info *info)
{
	// char	*unset;
	if (getenv(name))
	{
		// remove from info->env
		info->envp = del_str_from_array2d(info->envp, name, 0);
		return(0); // for only if condetion work
	}
	return (1);
}