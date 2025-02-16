# include "../minishell.h"

int	is_valid_qout(char **line)
{
	char	*dest;
	int		i;

	i = 0;
	while (line[0][i])
	{
		if (line[0][i] == '\"')
		{
			dest = double_quot_fun(&line[0][++i]);
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
		i++;
	}
	return (1);
}

int	check_valid_line(char **line)
{
	if (ft_strlen(line[0]) == 0)
		return (0);
	if ( line[0][0] == '|' || line[0][0] == '>' || line[0][0] == '<')
	{
		if (line[0][0] == '|' )
			printf ("bash: syntax error near unexpected token `|'\n");
		else
			printf ("bash: syntax error near unexpected token `newline'");
		line[0] = free_char(&line[0]);
		return (0);
	}
	if (line[0][strlen(line[0]) - 1] == '|')
	{
		if (line[0][0] == '|')
			printf ("error sentax\n");
		line[0] = free_char(line);
		return (0);
	}
	if(!is_valid_qout(line))
	{
		printf ("error sentax qoutition\n");
		line[0] = free_char(line);
		return (0);
	}
	return (1);
}
