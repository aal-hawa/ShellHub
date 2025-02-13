
#include "minishell.h"

void	unlink_files(t_info *info)
{
	int i;
	char *str;
	char	*str_i;
	i = 0;
	if (info->index_files_crt > 0)
	{
		while (i < info->index_files_crt)
		{
			str_i = ft_itoa(i);
			str = ft_strjoin("/tmp/tmp_shell_", str_i);
			unlink (str);
			str_i = free_char(&str_i);
			str = free_char(&str);
			i++;
		}
	}
}

// ls | grep "txt"
void	minishell(t_info *info)
{
	char	*line;
	int		is_error_127;

	while (1)
	{
		// char **tokens;
		// readLine && hestory
		line = readline_fun();
		printf("the input: %s\n", line);
		if (ft_strlen(line) == 0)
			continue ;
		create_nodes(line, info);

		if (info->first_node)
		{
			print_nodes(info->first_node);
			is_error_127 = execute_fun(info);
			unlink_files(info);
			// free_nodes(&nodes);
			if (is_error_127 == 1)
				exit(127);
			if (info->is_exit_one == 1)
				exit(1);
		}
		line = free_char(&line);
		reset_info(info);
		// nodes
		// syntax error
		// commands structure
	}
}
