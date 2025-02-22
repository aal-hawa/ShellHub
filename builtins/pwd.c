

# include "../minishell.h"

char	**pwd_fun(t_info *info, int is_print)
{
	char 	*cur_path;
	char	**result;

	cur_path = getcwd(NULL, 0);
	if (!cur_path)
	{
		info->status_exit = 1;
		return (NULL);
	}
	info->curent_path = ft_restore_value(&info->curent_path, &cur_path, 1);
	if (is_print == 1)
	printf("%s\n",info->curent_path);
	result = malloc(sizeof(char *) * 2);
	if (!result)
		return (NULL);
	result[0] = ft_strdup(info->curent_path);
	result[1] = NULL;
	return (result);
}
