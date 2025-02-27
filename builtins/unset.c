
# include "../minishell.h"

void	check_delete(char *arg, t_info *info)
{
	int		i;
	char	*key;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	key = ft_strndup(arg, i);
	printf("inside unset/check_delete key: %s\n", key);
	if (!check_is_valid_key(key))
	{
		printf("minishell: unset: `%s': not a valid identifier\n", key);
		free(key);
		return ;
	}
	if (is_exist_str_in_2array(info->export, key, 0) || 
		is_exist_str_in_2array(info->export, key, ft_strlen(arg)))
	{
		info->export = del_str_from_array2d(info->export, arg, 0);
	}
	if (is_exist_str_in_2array(info->envp, key, 0) || 
		is_exist_str_in_2array(info->envp, key, ft_strlen(arg)))
	{
		info->envp = del_str_from_array2d(info->envp, arg, 0);
	}
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
	}
	return (NULL);
}