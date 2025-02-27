# include "../minishell.h"

void	devide_line_be4_after(char **line, int i, char **str_be4, char **str_after)
{
	char	*str_join;
	if (i != 0)
	{
		*str_be4 = malloc(sizeof(char) * (i + 1));
		ft_strlcpy(*str_be4, *line, i);
		str_join = ft_strjoin(*str_be4, " ");
		*str_be4 = ft_restore_value(str_be4, &str_join, 1);
	}
	if (line[0][i + 1])
		*str_after = ft_strdup(&line[0][i + 1]);
}

char	*tilde(char **line, char *str_home)
{
	int		i;
	int		is_qout;
	char	*str_be4;
	char	*str_after;

	i = -1;
	is_qout = 0;
	str_be4 = NULL;
	str_after = NULL;
	while(line[0][++i])
	{
		if (is_qout == 0 && (line[0][i] == '~'))
		{
			if ((i == 0 || line[0][i - 1] == ' ') && (line[0][i + 1] == ' '
				|| line[0][i + 1] == '/' || !line[0][i + 1]))
			{
				devide_line_be4_after(line, i, &str_be4, &str_after);
				*line = marge_new_line(line, &str_be4, &str_after, str_home);
			}
		}
		is_qout = is_qout_fun(is_qout, line[0][i]);
	}
	return (*line);
}
