
# include "../minishell.h"

char	**change_path(char *cd, t_info *info, int is_print)
{
	// char	*result;
	char	*str_message;

	(void) is_print;
	if (chdir(info->curent_path))
	{
		printf ("%sError path: %s%s\n",info->colors->red_color, info->curent_path, info->colors->default_color); //delete this line
		pwd_fun(info, 0);
		info->status_exit = 1;
		str_message = builtins_error_message("cd", cd);
		builtins_Message(&str_message, 1, 1);
		return (NULL);
	}
	info->status_exit = 0;
	return (NULL);
}

char	**cd_fun(char **args, t_info *info, int is_print)
{
	char	*str;
	char	*cd;
	// char	*str_message;

	cd = args[1];
	// str_message = "bash: cd: too many arguments\n";
	// if (len_split(args) > 2)
	// {
	// 	builtins_Message(&str_message, 1, 0);
	// 	return (NULL);
	// }
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
	return(change_path(cd, info, is_print));
}
