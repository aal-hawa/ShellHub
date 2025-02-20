
# include "../minishell.h"

// send char *str from first char after single qoutes
// return NULL if did not have second single qoutes
// return malloc char * between the single qoutes
char	*single_quot_fun(char *str)
{
	if (!str)
		return (NULL);
	return (ft_strccpy(str,  '\''));

	// char	*dst;
	// char	*line_before_qout;
	// char	*line_after_qout;
	// // char	*str_join;

	// if (!str)
	// 	return (NULL);
	// line_after_qout = NULL;
	// line_before_qout = malloc(sizeof(char) * (i + 2));
	// ft_strlcpy(line_before_qout, *line, i + 1);
	// dst = ft_strccpy(str,  '\'');
	// if (dst && ft_strlen(dst) > 0)
	// 	line_after_qout = ft_strdup(&line[0][i + ft_strlen(dst)]);
	// if (dst)
	// 	dst = find_doller_sign_fun(&dst, info);
	// *line = marge_new_line(line, &line_before_qout, &line_after_qout, dst);	
	// // str_join = ft_strjoin(line_before_qout, dst);
	// // line_before_qout = free_char(&line_before_qout);	
	// // *line = ft_restore_value(line, &str_join, 1);
	// // if (line_after_qout)
	// // {
	// // 	str_join = ft_strjoin(*line, line_after_qout);
	// // 	line_after_qout = free_char(&line_after_qout);
	// // 	*line = ft_restore_value(line, &str_join, 1);
	// // }
	// return (dst);
}
