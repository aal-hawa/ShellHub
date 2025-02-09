

# include "../minishell.h"

char	*cd_fun(char *cd, t_info *info)
{
	char *str;

	if (!cd)
		info->curent_path = ft_restore_value(&info->curent_path, &info->home, 0);
	else if (!ft_strcmp(cd,".."))
		info->curent_path = ft_strlchr(&info->curent_path, '/', 1);
	else
	{
		str = ft_strjoin_p(info->curent_path, cd, 1);
		info->curent_path = ft_restore_value(&info->curent_path, &str, 1);
	}
	if (chdir(info->curent_path))
	{
		printf ("Error path: %s\n", info->curent_path);
		pwd_fun(info);
	}
	return(info->curent_path);
}
