# include "../minishell.h"

int	same_qout_order(char **line,char **str, int i, int j)
{
	if (str[0][j + 1] == line[0][i])
	{
		while(str[0][j + 2])
		{
			str[0][j] = str[0][j + 2];
			j++;
		}
		str[0][j] = '\0';
	}
	return (j);
}

void	before_qout(char **line, int i)
{
	int		j;
	char 	*str;
	char	c[2];

	c[0] = '\0';
	c[1] = '\0';
	if (i > 0)
		c[0] = line[0][i - 1];
	if (i != 0 && line[0][i - 1] != ' ' && line[0][i - 1] != line[0][i] && !is_operator_fun(c))
	{
		str = ft_strdup(*line);
		j = i;
		while (j > 0 && line[0][j - 1] && line[0][j - 1] != line[0][i] && !is_operator_fun(c))
		{
			str[j] = line[0][j - 1];
			j--;
			c[0] = line[0][j - 1];
		}
		str[j] = line[0][i];
		ft_restore_value(line, &str, 1);
	}
}

void	after_qout(char **line, int *adress_i)
{
	int		j;
	int		i;
	char 	*str;
	char	c[2];

	i = *(adress_i);
	c[0] = line[0][i + 1];
	c[1] = '\0';
	if (line[0][i + 1] && line[0][i + 1] != ' '
		&& line[0][i + 1] != line[0][i] && !is_operator_fun(c))
	{
		str = ft_strdup(*line);
		j = i;
		while (line[0][j + 1] && line[0][j + 1] != ' '
			&& line[0][j + 1] != line[0][i] && !is_operator_fun(c))
		{
			str[j] = line[0][j + 1];
			j++;
			c[0] = line[0][j + 1];
		}
		str[j] = line[0][i];
		j = same_qout_order(line, &str, i, j);
		ft_restore_value(line, &str, 1);
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
	}
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
			dest = free_string(&dest);
		}
		else if (line[0][i] == '\'')
		{
			dest = single_quot_fun(&line[0][++i]);
			if (!dest)
				return (0);
			i += ft_strlen(dest);
			dest = free_string(&dest);
		}
	}
	return (1);
}
