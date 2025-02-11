#include "../minishell.h"

void	dir_bilt_fun(t_node **node, char *before_tybe, t_info *info)
{
	if (!ft_strcmp(before_tybe, "<") || !ft_strcmp(before_tybe,"<<")
	 || !ft_strcmp(before_tybe,">") || !ft_strcmp(before_tybe,">>"))
		node[0]->is_dir_bilt_cmd = 0;
	else if (!ft_strcmp(node[0]->args[0], "cd") || !ft_strcmp(node[0]->args[0], "pwd") 
		|| !ft_strcmp(node[0]->args[0], "echo") || !ft_strcmp(node[0]->args[0], "env") || !ft_strcmp(node[0]->args[0], "export")
			||!ft_strcmp(node[0]->args[0], "unset") || !ft_strcmp(node[0]->args[0], "exit"))
		node[0]->is_dir_bilt_cmd = 1;
	else
	{
		node[0]->is_dir_bilt_cmd = 2;
		info->str_i++;
	}
}
void	type_after_fun(t_node **node, char **line, int i)
{

	if (line[0][i] != '|' && line[0][i + 1])
	{
		if (line[0][i] == '>' && line[0][i + 1] == '>')
			node[0]->type_after = ft_strdup(">>");
		else if (line[0][i] == '<' && line[0][i + 1] == '<')
			node[0]->type_after = ft_strdup("<<");
	}
	else
	{
		// node[0]->type_after = calloc(1, 2);
		node[0]->type_after = malloc(sizeof(char) * 2);
		node[0]->type_after[0] = line[0][i];
		node[0]->type_after[1] = '\0';
	}
}
t_node *	order_nodes(t_node **current_node)
{
	char	**args;
	char	*str_cmd;
	char	*space;
	char	*str_join;
	t_node	*file_nodes;
	t_node	*first_node;

	file_nodes = NULL;
	first_node = NULL;
	args = current_node[0]->args;
	space = " ";
	str_cmd = NULL;
	printf("1111-----------\n");
	file_nodes = malloc_node();
	if (!file_nodes)
		return (*current_node);
	first_node = file_nodes;
		

	while (*args)
	{
		printf("2222-----------0\n");
		// make new node of files
		if (is_operator_fun(*args) == 1)
		{
			printf("3333-----------0\n");
			if (file_nodes->args)
			{
				file_nodes->type_after = ft_strdup(*args);
				file_nodes->next = malloc_node();
				file_nodes = file_nodes->next;
			}
			file_nodes->type_before = ft_strdup(*args);
			args++;
			file_nodes->args = ft_split(*args, ' ');
			printf("3333-----------1\n");

		}
		else
		{
			printf("4444-----------0\n");
			// strjoin the command
			printf("str_cmd %s\n",str_cmd);

			if (str_cmd)
			{
				str_join =  ft_strjoin(str_cmd, space);
				str_cmd = ft_restore_value(&str_cmd, &str_join, 1);
			}
			printf("str_cmd %s\n",str_cmd);
			printf("*args %s\n",*args);

			str_join =  ft_strjoin(str_cmd, *args);
			printf("str_join %s\n",str_join);

			str_cmd = ft_restore_value(&str_cmd, &str_join, 1);

			printf("str_cmd %s\n",str_cmd);

			printf("4444-----------1\n");
		}
		if (args)
			args++;
		printf("2222-----------1\n");
	}
	// marge last node with the commands
	printf("5555-----------\n");
	if (!file_nodes->args)
		printf("file_nodes->args = NULL \n");
	if (!ft_split(str_cmd, ' '))
		printf("ft_split(str_cmd, ' ') = NULL \n");
	printf("str_cmd %s\n",str_cmd);
	
	file_nodes->args = marge_2_splits(file_nodes->args, ft_split(str_cmd, ' '));
	printf("6666-----------\n");

	str_cmd = free_char(&str_cmd);
	// replace and free current node
	printf("7777-----------\n");
	printf("first_node->is_dir_bilt_cmd %d\n",first_node->is_dir_bilt_cmd);
	printf("first_node->type_after %s\n",first_node->type_after);
	printf("first_node->type_before %s\n",first_node->type_before);
	printf("first_node->args[0] %s\n",first_node->args[0]);
	if (!first_node->type_after)
		first_node->type_after = ft_strdup(current_node[0]->type_after);
	if (!first_node->type_before)
		first_node->type_before = ft_strdup(current_node[0]->type_before);
	printf("first_node->is_dir_bilt_cmd %d\n",first_node->is_dir_bilt_cmd);
	printf("first_node->type_after %s\n",first_node->type_after);
	printf("first_node->type_before %s\n",first_node->type_before);
	printf("first_node->args[0] %s\n",first_node->args[0]);
	free_nodes(current_node);
	printf("8888-----------\n");
	printf("first_node->is_dir_bilt_cmd %d\n",first_node->is_dir_bilt_cmd);
	printf("first_node->type_after %s\n",first_node->type_after);
	printf("first_node->type_before %s\n",first_node->type_before);
	printf("first_node->args[0] %s\n",first_node->args[0]);
	return (first_node);
}

char	*insert_node(t_node **node, char **line, int i, int j)
{
	char	*cmd_order;
	char	*before_tybe;
	int		x;

	x = 0;
	printf("-----------\n");
	printf("line[0][j]: %c\n", line[0][j]);
	if (j != 0)
	{
		j++;
		printf("line[0][j + 1]: %c\n", line[0][j]);
	}
	printf("-----------\n");
	cmd_order = malloc(sizeof(char) * (i - j + 1));
	while (j < i)
	{
		cmd_order[x] = line[0][j];
		j++;
		x++;
	}
	cmd_order[x] = '\0';
	node[0]->args = ft_split(cmd_order, ' ');
	free(cmd_order);
	before_tybe = node[0]->type_after;
	return (before_tybe);
}
void	order_info_nodes(t_info *info)
{
	t_node *current_node;
	t_node *next_node;

	current_node = info->first_node;
	next_node = NULL;
	if (current_node)
		next_node = current_node->next;
	while (current_node)
	{
		current_node = order_nodes(&current_node);
		
		printf("FINISH: order_nodes\n");
		while (current_node)
			current_node = current_node->next;
		current_node = next_node;
		if (current_node)
			next_node = current_node->next;
		printf("current_node changed \n");

	}
	printf("FINISH WHILE: order_info_nodes\n");
}

void	create_nodes(char *line, t_info *info)
{
	t_node	*node;
	char	*before_tybe;
	int		i;
	int		j;

	j = 0;
	i = 0;
	node = malloc_node();
	if (!node)
	{
		info->first_node = NULL;
		return ;
	}
	node->type_before = ft_strdup("start");
	info->first_node = node;
	node->last_fd_name = NULL;
	while (line[i])
	{
		if (line[i] == '|')
		{
			type_after_fun(&node, &line, i);
			before_tybe = insert_node(&node, &line, i, j);
			dir_bilt_fun(&node, before_tybe, info);
			j = i;
			// node->next = NULL;
			node = malloc_node();
			node = node->next;
			node->type_before = ft_strdup(before_tybe);
		}
		i++;
	}
	node->type_after = ft_strdup("end");
	before_tybe = insert_node(&node, &line, i, j);
	dir_bilt_fun(&node, before_tybe, info);
	node->next = NULL;
	printf("info->first_node->is_dir_bilt_cmd %d\n",info->first_node->is_dir_bilt_cmd);
	printf("info->first_node->type_after %s\n",info->first_node->type_after);
	printf("info->first_node->type_before %s\n",info->first_node->type_before);
	printf("info->first_node->args[0] %s\n",info->first_node->args[0]);
	order_info_nodes(info);
	printf("FINISH: order_info_nodes\n");

	printf("info->first_node->is_dir_bilt_cmd %d\n",info->first_node->is_dir_bilt_cmd);
	printf("info->first_node->type_after %s\n",info->first_node->type_after);
	printf("info->first_node->type_before %s\n",info->first_node->type_before);
	printf("info->first_node->args[0] %s\n",info->first_node->args[0]);
}
