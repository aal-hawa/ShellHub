#include "../minishell.h"

char	*marge_new_line(char **line, char **str_be4, char **str_after, char *str_changed)
{
	// char	*str_join;

	// str_join = ft_strjoin(*str_be4, str_changed);
	// *line = ft_restore_value(line, &str_join, 1);
	// *line = ft_join_with_restore(line, *str_be4, str_changed, NULL);
	*line = ft_join_with_restore(line, *str_be4, str_changed, *str_after);
	*str_be4 = free_string(str_be4);	
	*str_after = free_string(str_after);
	// if (str_after && *str_after)
	// {
	// 	// str_join = ft_strjoin(*line, *str_after);
	// 	// *line = ft_restore_value(line, &str_join, 1);
	// 	*line = ft_join_with_restore(line, *line, *str_after, NULL);
	// 	*str_after = free_string(str_after);

	// }
	return (*line);
}
