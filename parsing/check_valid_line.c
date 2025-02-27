# include "../minishell.h"

char	next_char_not_space(char *line, int is_second)
{
	int	i;

	i = 0;
	while(line[++i])
	{
		if (line[i] != ' ')
		{
			if (is_second == 0)
				return (line[i]);
			else
				is_second = 0;
		}
	}
	return ('\0');
}

int	check_valid_operator(char **line)
{
	int		i;

	i = 0;
	while (line[0][i] == ' ')
		i++;
	while(line[0][i])
	{	
		if (is_char_operator_fun(line[0][i]) && line[0][i] != '|' && is_char_operator_fun(next_char_not_space(&line[0][i], 0))
			&& is_char_operator_fun(next_char_not_space(&line[0][i], 1)))
			return (0);
		if (is_char_operator_fun(line[0][i])  && next_char_not_space(&line[0][i], 0) == '|' )
			return (0);
		if ( line[0][i] == '>' && next_char_not_space(&line[0][i], 0) == '<' )
			return (0);
		if ( line[0][i] == '<' && next_char_not_space(&line[0][i], 0) == '>' )
			return (0);
		if ( line[0][i] == '>' && line[0][i + 1] == ' ' && next_char_not_space(&line[0][i], 0) == '>' )
			return (0);
		if ( line[0][i] == '<' && line[0][i + 1] == ' ' && next_char_not_space(&line[0][i], 0) == '<' )
			return (0);
		i++;
		while (line[0][i] == ' ')
			i++;
	}
	return (1);
}

int	check_first_last_line(char **line)
{
	int	i;

	i = 0;
	while (line[0][i] == ' ')
		i++;
	if (line[0][i] == '|')
	{
		printf ("bash: syntax error near unexpected token `|'\n");
		line[0] = free_char(&line[0]);
		return (0);
	}
	i = strlen(line[0]) - 1;
	while (i > 0 && line[0][i] == ' ')
		i--;
	if (line[0][i] == '|' || line[0][i] == '>' || line[0][i] == '<')
	{
		if (line[0][i] == '|')
			printf ("error syntax\n");
		else
			printf ("bash: syntax error near unexpected token `newline'\n");
		line[0] = free_char(line);
		return (0);
	}
	return (1);
}

int	check_valid_line(char **line, t_info *info)
{
	if (ft_strlen(line[0]) == 0)
		return (0);
	if(!check_first_last_line(line))
		return (0);
	if(!check_valid_operator(line))
	{
		printf ("error syntax parsing\n");
		line[0] = free_char(line);
		return (0);
	}
	*line = chck_spacesbetween_qout(line);
	if(!is_valid_qout(line, info))
	{
		printf ("error syntax qoutition\n");
		line[0] = free_char(line);
		return (0);
	}
	return (1);
}
