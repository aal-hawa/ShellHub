
# include "../minishell.h"

void	check_delete(char *arg, t_info *info)
{
	int		i;
	char	*export_arg;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] == '=')
		return ;
	export_arg = NULL;
	export_arg = ft_join_with_restore(&export_arg, "declare -x ", arg, NULL);
	info->export = del_str_from_array2d(&info->export, export_arg);
	info->envp = del_str_from_array2d(&info->envp, arg);
	export_arg = free_string(&export_arg);
}

char	**unset_func(char **args, t_info *info)
{
	int i;

	i = 1;
	if(args[i])
	{
		while(args[i])
		{
			check_delete(args[i], info);
			i++;
		}
		env_data(info);
	}
	return (NULL);
}