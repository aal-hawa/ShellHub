

# include "../minishell.h"

char	**pwd_fun(t_info *info, int is_print)
{
	char 	*cur_path;
	char	*str_join;

	cur_path = getcwd(NULL, 0);
	if (!cur_path)
	{
		info->status_exit = 1;
		return (NULL);
	}
	info->status_exit = 0;
	info->curent_path = ft_restore_value(&info->curent_path, &cur_path, 1);
	str_join = ft_strjoin(info->curent_path, "\n");
	if (is_print == -1)
	{
		str_join = free_string(&str_join);
		return (NULL);
	}
	return (builtins_Message(&str_join, is_print, 1));
}
