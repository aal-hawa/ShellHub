
# include "../minishell.h"

char	**more_args_Massege(char **str_massege, int is_print, int is_malloc)
{
	char	**result;

	if (is_print == 1)
		printf ("%s", *str_massege);
	result = malloc(sizeof(char *) * 2);
	if (!result)
		return (NULL);
	result[0] = ft_strdup(*str_massege);
	result[1] = NULL;
	if (is_malloc == 1)
		*str_massege = free_char(str_massege);
	return(result);
}

char	**change_path(char *cd, t_info *info, int is_print)
{
	char	*result;
	char	*str_massege;

	if (chdir(info->curent_path))
	{
		printf ("%sError path: %s%s\n",info->colors->red_color, info->curent_path, info->colors->default_color); //delete this line
		pwd_fun(info, 0);
		str_massege = ft_strjoin("bash: cd: ", cd);
		result = ft_strjoin(str_massege, ": No such file or directory\n");
		str_massege = ft_restore_value(&str_massege, &result, 1);
		return(more_args_Massege(&str_massege, is_print, 1));
	}
	return(NULL);
}

char	**cd_fun(char **args, t_info *info, int is_print)
{
	char	*str;
	char	*cd;
	char	*str_massege;

	cd = args[1];
	str_massege = "bash: cd: too many arguments\n";
	if (len_split(args) > 2)
		return (more_args_Massege(&str_massege, is_print, 0));
	if (!cd)
		info->curent_path = ft_restore_value(&info->curent_path, &info->home, 0);
	else if (cd[0] == '/' || (!ft_strncmp(cd,"..", 2) && ft_strlen(cd) > 2))
		info->curent_path = ft_restore_value(&info->curent_path, &cd, 0);
	else
	{
		if (!ft_strcmp(cd,".."))
			str = ft_strdup("../");
		else
			str = ft_strjoin_p(info->curent_path, cd, 1);
		info->curent_path = ft_restore_value(&info->curent_path, &str, 1);
	}
	return(change_path(cd, info, is_print));
}
