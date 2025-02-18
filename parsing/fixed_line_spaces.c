# include "../minishell.h"

int		add_more_spaces(char **line)
{
	int		i;
	int		j;
	int		is_qout;

	if (!line || !*line)
		return (0);
	i = 0;
	j = 0;
	is_qout = 0;
	while(line[0][i])
	{
		if (i != 0 && is_qout == 0 && is_char_operator_fun(line[0][i]) && line[0][i - 1] != ' ' && line[0][i - 1] != line[0][i])
			j++;
		if (is_qout == 0 && is_char_operator_fun(line[0][i]) && line[0][i + 1] != ' ' && line[0][i + 1] != line[0][i])
			j++;
		is_qout = is_qout_fun(is_qout, line[0][i]);
		i++;
	}
	return (j);
}

void	fixed_line_spaces(char **line)
{
	int		i;
	int		j;
	int		len;
	int		is_qout;
	char 	*dest;

	if (!line || !*line)
		return ;
	i = 0;
	j = 0;
	is_qout = 0;
	len = add_more_spaces(line);
	if (len == 0)
		return ;
	len += strlen(*line);
	printf("len %d\n", len);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return ;
	while(line[0][i])
	{
		if (i != 0 && is_qout == 0 && i != 0 && is_char_operator_fun(line[0][i])
			&& line[0][i - 1] != ' ' && line[0][i - 1] != line[0][i])
			dest[j++] = ' ';
		dest[j++] = line[0][i];
		if (is_qout == 0 && is_char_operator_fun(line[0][i])
			&& line[0][i + 1] != ' ' && line[0][i + 1] != line[0][i])
			dest[j++] = ' ';
		is_qout = is_qout_fun(is_qout, line[0][i]);
		i++;
	}
	dest[j] = '\0';
	printf("strlen dest %ld\n",strlen(dest));
	*line = free_char(line);
	*line = dest;
}
