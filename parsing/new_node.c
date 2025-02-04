#include "../minishell.h"

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

// typedef struct s_node
// {
// 	char			**args;
// 	char			*type_before;
// 	char			*type_after;
// 	struct s_node	*next;
// 	int				is_dir_bilt_cmd;
// }					t_node;

// char	**ft_split(char const *s, char c);
void	dir_bilt_fun(t_node **node, char *before_tybe)
{
	if (ft_strcmp(before_tybe, "start") && ft_strcmp(before_tybe,"|"))
		node[0]->is_dir_bilt_cmd = 0;
	else if (!ft_strcmp(node[0]->args[0], "cd") || !ft_strcmp(node[0]->args[0], "pwd") 
		|| !ft_strcmp(node[0]->args[0], "echo") || !ft_strcmp(node[0]->args[0], "env") || !ft_strcmp(node[0]->args[0], "export")
			||!ft_strcmp(node[0]->args[0], "unset") || !ft_strcmp(node[0]->args[0], "exit"))
		node[0]->is_dir_bilt_cmd = 1;
	else 
		node[0]->is_dir_bilt_cmd = 2;
}
void	type_after_fun(t_node **node, char **line, int i)
{
	if (line[0][i] != '|' && line[0][i + 1])
	{
		if (line[0][i] == '>' && line[0][i + 1] == '>')
			node[0]->type_after = strdup(">>");
		else if (line[0][i] == '<' && line[0][i + 1] == '<')
			node[0]->type_after = strdup("<<");
	}
	else
	{
		node[0]->type_after = calloc(1, 2);
		node[0]->type_after[0] = line[0][i];
	}
}

char	*insert_node(t_node **node, char **line, int i, int j)
{
	char	*cmd_order;
	char	*before_tybe;

	cmd_order = malloc(sizeof(char) * (i - j + 1));
	while (j < i)
	{
		cmd_order[j] = line[0][j];
		j++;
	}
	cmd_order[j] = '\0';
	node[0]->args = ft_split(cmd_order, ' ');
	free(cmd_order);
	before_tybe = node[0]->type_after;
	return (before_tybe);
}

void	create_nodes(char *line, t_info *info)
{
	t_node	*node;
	// t_node	*next_node;
	char	*before_tybe;
	int		i;
	int		j;

	j = 0;
	i = 0;
	node = malloc(sizeof(t_node));
	if (!node)
	{
		info->first_node = NULL;
		return ;
	}
	node->type_before = strdup("start");
	info->first_node = node;
	printf("before setting last node\n");
	while (line[i])
	{
		if (line[i] == '|' || line[i] == '>' || line[i] == '<')
		{
			type_after_fun(&node, &line, i);
			before_tybe = insert_node(&node, &line, i, j);
			dir_bilt_fun(&node, before_tybe);
			j = i;
			node->next = NULL;
			node = node->next;
			node = malloc(sizeof(t_node));
			// next_node = node;
			node->type_before = strdup(before_tybe);
			printf("aaaaaaaaaaaaaaaaaaaaa\n");
		}
		i++;
	}
	node->type_after = strdup("end");
	before_tybe = insert_node(&node, &line, i, j);
	dir_bilt_fun(&node, before_tybe);
	node->next = NULL;
}
// ls | grep	r00