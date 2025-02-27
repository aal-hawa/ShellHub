#include "../minishell.h"

void	print_nodes(t_node *nodes, t_colors *colors)
{
	printf("%s\n-----------------------------\n%s",colors->green_color,colors->default_color);
	if (!nodes || !nodes->args)
	{
		printf("%s\n---------------ERROR--------------\n%s",colors->red_color,colors->default_color);
		return ;
	}
	while (nodes)
	{
		printf("%sArgs: %s", colors->blue_color,colors->default_color);
		for (int i = 0; nodes->args[i]; i++)
		printf("%s ", nodes->args[i]);
		printf("%s\nType Before: %s, Type After: %s, is_dir_bilt_cmd: %d\n%s",
			colors->magenta_color, nodes->type_before, nodes->type_after, nodes->is_dir_bilt_cmd, colors->default_color);
		nodes = nodes->next;
		}
	printf("%s\n-----------------------------\n%s",colors->default_color,colors->default_color);
}
