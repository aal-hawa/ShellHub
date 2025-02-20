#include "../minishell.h"



char	*marge_new_line(char **line, char **str_be4, char **str_after, char *str_changed)
{
	char	*str_join;

	str_join = ft_strjoin(*str_be4, str_changed);
	*str_be4 = free_char(str_be4);	
	*line = ft_restore_value(line, &str_join, 1);
	if (str_after && *str_after)
	{
		str_join = ft_strjoin(*line, *str_after);
		*str_after = free_char(str_after);
		*line = ft_restore_value(line, &str_join, 1);
	}
	return (*line);
}
