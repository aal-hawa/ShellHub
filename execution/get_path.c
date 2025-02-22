
# include "../minishell.h"

void	env_data(char **envp, char **env, t_info *info)
{
	int	i;

	i = 0;
	*env = NULL;
	if (envp)
	{
		while (envp[i])
		{
			if (ft_strncmp(envp[i], "HOME=", 5) == 0)
				info->home = ft_strdup(&envp[i][5]);
			if (ft_strncmp(envp[i], "PATH=", 5) == 0)
				*env = &envp[i][5];
			i++;
		}
	}
}

int	is_access_str_cmd(char ***env_split, char *str_joined, char *str)
{
	if (!str_joined)
	{
		ft_putstr_fd_malloc(ft_strjoin("zsh: command not found: ", str), 2, 2);
		free_array2d(env_split, 0);
		return (-1);
	}
	if (!access(str_joined, R_OK))
	{
		free_array2d(env_split, 0);
		return (1);
	}
	return (0);
}

char	*get_from_env(char *env, char *str)
{
	int		i;
	char	**env_split;
	char	*str_joined;
	int		is_access;

	if (!env)
		return (NULL);
	i = -1;
	env_split = ft_split(env, ':');
	if (!env_split)
		return (NULL);
	while (env_split[++i])
	{
		str_joined = ft_strjoin_path(env_split[i], str, 1);
		is_access = is_access_str_cmd(&env_split, str_joined, str);
		if (is_access == -1)
			return (NULL);
		if (is_access == 1)
			return (str_joined);
		str_joined = free_char(&str_joined);
	}
	free_array2d(&env_split, 0);
	ft_putstr_fd_malloc(ft_strjoin("zsh: command not found: ", str), 2, 2);
	return (NULL);
}

void	get_path_command(char **strs, t_info *info)
{
	int		i;

	i = 0;
	if (strs[0])
	{
		while (strs[0][i])
		{
			if (strs[0][i] == '.' || strs[0][i] == '/')
			{
				info->path_commd = ft_strdup(strs[0]);
				break ;
			}
			i++;
		}
		if (!strs[0][i])
			info->path_commd = get_from_env(info->env, strs[0]);
	}
}
