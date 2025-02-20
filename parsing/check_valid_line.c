# include "../minishell.h"

int	before_qout(char **line, char **str, int i, int y)
{
	int	j;

	if ( i != 0 && line[0][i - 1] != ' ')
	{
		j = i - 1;
		while (j > 0 && line[0][j] != ' ')
			j--;
		while (++y <= j)
			str[0][y] = line[0][y];
		str[0][y] = line[0][i];
		while (++y < i)
			str[0][y] = line[0][y];
	}
	return (y);
}

int	after_qout(char **line, char **str, int i, int y)
{
	int	j;

	if (line[0][i + 1] && line[0][i + 1] != ' ')
	{
		j = i + 1;
		while (line[0][j] && line[0][j] != ' ')
			j++;
		while (++y < j)
			str[0][y] = line[0][y + 1];
		str[0][y] = line[0][i];
		// while (++y < i)
		// 	str[0][y] = line[0][y];
	}
	return (y);
}


char	*chck_spacesbetween_qout(char **line)
{
	char	*str;
	int		i;
	int		y;
	int		is_qout;

	i = -1;
	y = ft_strlen(*line);
	str = malloc(sizeof(char) * (y + 1));
	y = -1;
	is_qout = 0;
	while (line[0][++i])
	{
		if (line[0][i] == '\'' || line[0][i] == '\"')
		{
			if (is_qout == 0)
				y = before_qout(line, &str, i, y);
			else
				y = after_qout(line, &str, i, y);
		}
		is_qout = is_qout_fun(is_qout, line[0][i]);
	}
	while (++y < i)
		str[y] = line[0][y];
	str[y] = '\0';
	return (ft_restore_value(line, &str, 1));
}

int	is_valid_qout(char **line, t_info *info)
{
	char	*dest;
	int		i;

	i = -1;
	while (line[0][++i])
	{
		if (line[0][i] == '\"')
		{
			i++;
			dest = double_quot_fun(line, i, &line[0][i], info);
			if (!dest)
				return (0);
			i += ft_strlen(dest);
			dest = free_char(&dest);
		}
		else if (line[0][i] == '\'')
		{
			dest = single_quot_fun(&line[0][++i]);
			if (!dest)
				return (0);
			i += ft_strlen(dest);
			dest = free_char(&dest);
		}
	}
	return (1);
}

int	check_valid_line(char **line, t_info *info)
{
	if (ft_strlen(line[0]) == 0)
		return (0);
	if (line[0][0] == '|')
	{
		printf ("bash: syntax error near unexpected token `|'\n");
		line[0] = free_char(&line[0]);
		return (0);
	}
	if (line[0][strlen(line[0]) - 1] == '|' || line[0][strlen(line[0]) - 1] == '>' || line[0][strlen(line[0]) - 1] == '<')
	{
		if (line[0][0] == '|')
			printf ("error syntax\n");
		else
			printf ("bash: syntax error near unexpected token `newline'\n");
		line[0] = free_char(line);
		return (0);
	}
	*line = chck_spacesbetween_qout(line);
	printf ("line %s\n", *line);

	if(!is_valid_qout(line, info))
	{
		printf ("error syntax qoutition\n");
		line[0] = free_char(line);
		return (0);
	}
	return (1);
}
