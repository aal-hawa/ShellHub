

# include "../minishell.h"

char	**cd_fun(char **args, t_info *info, int is_print)
{
	char *str;
	char *cd;
	char	**result;

	cd = args[1];
	if (len_split(args) > 2)
	{
		if (is_print == 1)
			printf ("bash: cd: too many arguments\n");
		result = malloc(sizeof(char *) * 2);
		if (!result)
			return (NULL);
		result[0] = ft_strdup("bash: cd: too many arguments\n");
		result[1] = NULL;
		return(result);
	}
	if (!cd) // || (cd && ft_strcmp(cd, "~"))
		info->curent_path = ft_restore_value(&info->curent_path, &info->home, 0);
	else if (cd[0] == '/')
		info->curent_path = ft_restore_value(&info->curent_path, &cd, 0);
	else if (!ft_strcmp(cd,".."))
		info->curent_path = ft_strlchr(&info->curent_path, '/', 1);
	else
	{
		str = ft_strjoin_p(info->curent_path, cd, 1);
		info->curent_path = ft_restore_value(&info->curent_path, &str, 1);
	}
	if (chdir(info->curent_path))
	{
		printf ("%sError path: %s%s\n",info->colors->red_color, info->curent_path, info->colors->default_color);
		pwd_fun(info, 0);
	}
	return(NULL);
}
