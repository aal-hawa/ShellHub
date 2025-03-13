
# include "../minishell.h"

void 	change_in_env(char **old_path, t_info *info)
{
	char	**args;

	args = NULL;
	args = add_in_array2d(&args, "export", 0);
	args = add_in_array2d(&args, *old_path, 0);
	*old_path = free_string(old_path);
	export_fun(args, info, 0);
	pwd_fun(info, -1);
	args[1] = free_string(&args[1]);
	args[1] = ft_strjoin("PWD=", info->curent_path);
	export_fun(args, info, 0);
	free_array2d(&args, 0);
}

char	**change_path(char *cd, t_info *info)
{
	// char	*result;
	char	*str_message;
	char *old_path;
	
	old_path = ft_strjoin("OLDPWD=", info->curent_path);
	if (chdir(info->curent_path))
	{
		printf ("%sError path: %s%s\n",info->colors->red_color, info->curent_path, info->colors->default_color); //delete this line
		pwd_fun(info, 0);
		info->status_exit = 1;
		str_message = builtins_error_message("cd", cd);
		builtins_Message(&str_message, 1, 1);
		old_path = free_string(&old_path);
		return (NULL);
	}
	change_in_env(&old_path, info);
	info->status_exit = 0;
	return (NULL);
}

char	**cd_fun(char **args, t_info *info)
{
	char	*str;
	char	*cd;

	cd = args[1];
	if (!cd)
		info->curent_path = ft_restore_value(&info->curent_path, &info->home, 0);
	else if (cd[0] == '/' || (!ft_strncmp(cd,"..", 2) && ft_strlen(cd) > 2))
		info->curent_path = ft_restore_value(&info->curent_path, &cd, 0);
	else
	{
		if (!ft_strcmp(cd,".."))
			str = ft_strdup("../");
		else
			str = ft_strjoin_path(info->curent_path, cd, 1);
		info->curent_path = ft_restore_value(&info->curent_path, &str, 1);
	}
	return(change_path(cd, info));
}
