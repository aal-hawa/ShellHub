
# include "../minishell.h"

char	**unset_func(char **args, t_info *info)
{
	// char	*unset;
	if (getenv(*args))
	{
		// remove from info->env
		info->envp = del_str_from_array2d(info->envp, *args, 0);
		return(0); // for only if condetion work
	}
	return (NULL);
}