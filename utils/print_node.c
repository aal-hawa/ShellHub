#include "../minishell.h"

void	print_tokens(t_token *token, t_colors *colors)
{
	printf("%s\n-----------------------------\n%s",colors->yellow_color,colors->default_color);
	if (!token)
	{
		printf("%s\n---------------ERROR--------------\n%s",colors->red_color,colors->default_color);
		return ;
	}

	while (token)
	{
		if (token->cmd)
		{
			printf("%scmd: %s", colors->blue_color,colors->default_color);
			for (int i = 0; token->cmd[i]; i++)
				printf("%s ", token->cmd[i]);
		}
		if (token->redirect)
		{
			printf("\n%sredirect: %s\n", colors->cyan_color,colors->default_color);
			print_nodes(token->redirect, colors);
		}
		// if (token->output_redirect)
		// {
		// 	printf("\n%soutput_redirect: %s\n", colors->cyan_color,colors->default_color);
		// 	print_nodes(token->output_redirect, colors);
		// }
		token = token->next;
		if (token)
			printf("\n---------\n");
	}
	printf("%s\n-----------------------------\n%s",colors->default_color,colors->default_color);
}

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
		printf("%s\nType Before: %s\n%s",
			colors->magenta_color, nodes->type_before, colors->default_color);
		nodes = nodes->next;
		}
	printf("%s\n-----------------------------\n%s",colors->green_color,colors->default_color);
}
