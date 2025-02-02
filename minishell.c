
#include "minishell.h"
// ls | grep "txt"
char	*minishell(t_info *info)
{
	char	*line;
	char **tokens;
	t_node	*nodes;
	int		is_error_127;

	while (1)
	{
		// char **tokens;
		// readLine && hestory
		line = readline_fun();
		printf("the input: %s\n", line);
		tokens = tokens_fun(line);
		while(*tokens)
			printf("the tokens: %s\n", *tokens++);
		nodes = nodes_init(tokens, info);
		if (nodes)
		{
			print_nodes(nodes);
			is_error_127 = my_pipe(nodes, &info);
			if (ft_strncmp(arg[1], "here_doc", 8) == 0 && info->fd_file_w != -1)
				unlink ("/tmp/tmp_pipe");
			if (is_error_127 == 1)
				exit(127);
			if (info->is_exit_one == 1)
				exit(1);
			free_nodes(&nodes);
		}
		free(line);
		// nodes
		// syntax error
		// commands structure
	}
}
