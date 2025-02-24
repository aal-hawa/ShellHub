# include "../minishell.h"

int	check_valid_operator(char **line)
{
	int	i;

	i = 0;
	while(line[0][i])
	{
		if (is_char_operator_fun(line[0][i]) && line[0][i + 1] && is_char_operator_fun(line[0][i + 1])
			&& line[0][i + 2] && is_char_operator_fun(line[0][i + 2]) && line[0][i + 2])
			return (0);
		if (line[0][i]  == '|' && line[0][i + 1] && is_char_operator_fun(line[0][i + 1]))
			return (0);
		if (is_char_operator_fun(line[0][i])  && line[0][i + 1] && line[0][i + 1] == '|' )
			return (0);
		if ( line[0][i] == '>' && line[0][i + 1] && line[0][i + 1] == '<' )
			return (0);
		if ( line[0][i] == '<' && line[0][i + 1] && line[0][i + 1] == '>' )
			return (0);
		i++;
	}
	return (1);
}

int	check_first_last_line(char **line)
{
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
		printf ("error syntax qoutition\n");
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
