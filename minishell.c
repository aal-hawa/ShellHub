
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
			str_i = free_string(&str_i);
			str = free_string(&str);
			i++;
		}
	}
	info->index_files_crt = 0;
}

void	show_leek(t_info *info)
{
	//----------------------------------------//
	// rl_clear_history();
	free_info(info);
	exit (0);
	//----------------------------------------//
}
// ls | grep "txt"
void	minishell(t_info *info)
{
	char	*line;
	// int		is_error_127;

	while (1)
	{
		// char **tokens;
		// readLine && hestory
		line = readline_fun();
		printf("%sthe input: %s%s\n", info->colors->cyan_color, info->colors->default_color, line);
		if (!check_valid_line(&line, info))
			continue ;
		fixed_line_spaces(&line);
		line = find_doller_sign_fun(&line, info);
		line = tilde(&line, info->home);
		create_nodes(line, info);
		line = free_string(&line);

		if (info->first_node)
		{
			print_nodes(info->first_node, info->colors);
			// is_error_127 = execute_fun(info);
			execute_fun(info);
			unlink_files(info);
			// free_nodes(&nodes);
			// if (is_error_127 == 1)
			// 	exit(127);
			// if (info->is_exit_one == 1)
			// 	exit(1);
		}
		// free_node(&info->first_node);
		reset_info(info);
		// nodes
		// syntax error
		// commands structure
	}
}
