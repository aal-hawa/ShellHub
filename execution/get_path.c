
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

char	*get_from_env(char *env, char *str, t_info *info)
{
	int		i;
	char	**env_split;
	char	*joined;

	if (!env)
		return (NULL);
	i = 0;
	env_split = ft_split_p(env, ':', info);
	if (!env_split)
		return (NULL);
	while (env_split[i])
	{
		joined = ft_strjoin_p(env_split[i], str, 1);
		if (!joined)
			return (ft_putstr_fd_p(
					ft_strjoin_p("zsh: command not found: ", str, 0), 2, 2),
				free_split(env_split, info->i_split), NULL);
		if (!access(joined, R_OK))
			return (free_split(env_split, info->i_split), joined);
		free_char(joined);
		i++;
	}
	free_split(env_split, info->i_split);
	return (ft_putstr_fd_p(ft_strjoin_p("zsh: command not found: ", str, 0), 2, 2),
		NULL);
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
			info->path_commd = get_from_env(info->env, strs[0], info);
	}
}
