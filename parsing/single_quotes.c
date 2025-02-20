
# include "../minishell.h"

// send char *str from first char after single qoutes
// return NULL if did not have second single qoutes
// return malloc char * between the single qoutes
char	*single_quot_fun(char **line, int i, char *str, t_info *info)
{
	char	*dst;
	char	*line_before_qout;
	char	*line_after_qout;
	char	*str_join;

	if (!str)
		return (NULL);
	line_after_qout = NULL;
	line_before_qout = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(line_before_qout, *line, i + 1);
	printf("line_before_qout %s\n", line_before_qout);

	dst = ft_strccpy(str,  '\'');
	if (dst && ft_strlen(dst) > 0)
		line_after_qout = ft_strdup(&line[0][i + ft_strlen(dst)]);
	printf("line_after_qout %s\n", line_after_qout);
	
	printf("dst0 %s\n", dst);
	if (dst)
		dst = find_doller_sign_fun(&dst, info);
	printf("dst1 %s\n", dst);
	str_join = ft_strjoin(line_before_qout, dst);
	printf("str_join %s\n", str_join);
	line_before_qout = free_char(&line_before_qout);	
	*line = ft_restore_value(line, &str_join, 1);
	printf("*line0 %s\n", *line);
	if (line_after_qout)
	{
		str_join = ft_strjoin(*line, line_after_qout);
		line_after_qout = free_char(&line_after_qout);
		*line = ft_restore_value(line, &str_join, 1);
	}
	printf("*line1 %s\n", *line);
	return (dst);
}
