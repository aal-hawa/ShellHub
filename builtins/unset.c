
# include "../minishell.h"

int	unset_func(char *name, t_info *info)
{
	// char	*unset;
	if (getenv(name))
	{
		// remove from info->env
		info->envp = del_from_split(info->envp, name);
		return(0); // for only if condetion work
	}
	return (1);
}