# include "../minishell.h"

void	before_qout(char **line, int i)
{
	int		j;
	char 	*str;

	if ( i != 0 && line[0][i - 1] != ' ')
	{
		printf ("before_qout\n");
		str = ft_strdup(*line);
		j = i;
		while (j > 0 && line[0][j - 1] && line[0][j - 1] != ' ')
		{
			str[j] = line[0][j - 1];
			j--;
		}
		str[j] = line[0][i];
		ft_restore_value(line, &str, 1);
		printf ("line[0]: %s\n", line[0]);
	}
}

void	after_qout(char **line, int *adress_i)
{
	int		j;
	int		i;
	char 	*str;

	i = *(adress_i);
	if (line[0][i + 1] && line[0][i + 1] != ' ')
	{
		printf ("after_qout\n");

		str = ft_strdup(*line);
		j = i;
		while (line[0][j + 1] && line[0][j + 1] != ' ')
		{
			str[j] = line[0][j + 1];
			j++;
		}
		str[j] = line[0][i];
		ft_restore_value(line, &str, 1);
		printf ("line[0]: %s\n", line[0]);
		*(adress_i) = j;
	}
}


char	*chck_spacesbetween_qout(char **line)
{
	int		i;
	int		is_qout;
	char	c;

	i = -1;
	is_qout = 0;
	while (line[0][++i])
	{
		c = line[0][i];
		if (line[0][i] == '\'' || line[0][i] == '\"')
		{
			if (is_qout == 0)
				before_qout(line, i);
			else
				after_qout(line, &i);
		}
		is_qout = is_qout_fun(is_qout, c);
		printf("line[0][i]: %c ", c);
		printf("is_qout: %d\n", is_qout);
	}
	printf("str: %s\n", *line);
	return (*line);
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
