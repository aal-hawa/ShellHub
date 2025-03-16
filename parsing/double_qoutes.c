
# include "../minishell.h"

// send char *str from first char after double qoutes
// return NULL if did not have second double qoutes
// return malloc char * between the double qoutes
char	*double_quot_fun(char **line, int i, char *str, t_info *info)
{
	char	*dst;
	char	*line_before_qout;
	char	*line_after_qout;

	if (!str)
		return (NULL);
	line_after_qout = NULL;
	line_before_qout = malloc(sizeof(char) * (i + 2));
	ft_strlcpy(line_before_qout, *line, i + 1);
	dst = ft_strccpy(str,  '\"');

	if (dst)
	{
		line_after_qout = ft_strdup(&line[0][i + ft_strlen(dst)]);
		dst = find_doller_sign_fun(&dst, info);
	}
	*line = join_with_restore(line, line_before_qout, dst, line_after_qout);
	line_before_qout = free_string(&line_before_qout);	
	line_after_qout = free_string(&line_after_qout);
	return (dst);
}
