#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../minishell.h"

typedef struct s_node
{
	char			**args;
	char			*type_before;
	char			*type_after;
	struct s_node	*next;
	int				is_dir_bilt_cmd;
}					t_node;

int	is_redirection_cmd(const char *cmd)
{
	int			i;
	const char	*redirections[] = {">", "<", ">>", "<<", NULL};

	for (i = 0; redirections[i]; i++)
	{
		if (ft_strcmp(cmd, redirections[i]) == 0)
			return (1);
	}
	return (0);
}

int	is_builtin_cmd(const char *cmd)
{
	int			i;
	const char	*builtins[] = {"cd", "pwd", "echo", "export", "unset", "env",
			"exit", NULL};

	for (i = 0; builtins[i]; i++)
	{
		if (ft_strcmp(cmd, builtins[i]) == 0)
			return (1);
	}
	return (0);
}

void	free_nodes(t_node **nodes)
{
	t_node	*temp;

	while (*nodes)
	{
		temp = *nodes;
		*nodes = (*nodes)->next;
		if (temp->args)
		{
			for (int i = 0; temp->args[i]; i++)
				free(temp->args[i]);
			free(temp->args);
		}
		free(temp->type_before);
		free(temp->type_after);
		free(temp);
	}
}

t_node	*create_node(char **args, const char *type_before,
		const char *type_after, t_info *info)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->args = args;
	node->type_before = type_before ? ft_strdup(type_before) : NULL;
	node->type_after = type_after ? ft_strdup(type_after) : NULL;
	node->next = NULL;
	node->is_dir_bilt_cmd = is_builtin_cmd(args[0]) ? 1 : is_redirection_cmd(type_before) ? 0 : 2;
	if (node->is_dir_bilt_cmd == 2)
		info->str_i++;
	return (node);
}

static int	create_last_node(char **args, char *type_before, t_node *head,
		t_node *current, t_info *info)
{
	t_node	*new_node;

	new_node = create_node(args, type_before, "end", info);
	if (!new_node)
	{
		free(type_before);
		free_nodes(&head);
		return (0);
	}
	if (!head)
		head = new_node;
	else
		current->next = new_node;
	return (1);
}

static int	create_new_node(char **args, char *type_after, char **type_before,
		t_node **head, t_node **current, t_info *info)
{
	t_node	*new_node;

	if (args)
	{
		new_node = create_node(args, *type_before, type_after, info);
		if (!new_node)
		{
			free(*type_before);
			free(type_after);
			free_nodes(head);
			return (0);
		}
		if (!*head)
			*head = new_node;
		else
			(*current)->next = new_node;
		*current = new_node;
	}
	free(*type_before);
	*type_before = type_after;
	return (1);
}

static int	handle_special_token(char *token, char ***args, char **type_after,
		char **type_before, t_node **head, t_node **current, t_info *info)
{
	*type_after = strdup(token);
	if (!create_new_node(*args, *type_after, type_before, head, current, info))
		return (0);
	*args = NULL;
	return (1);
}

static int	process_single_token(char *token, char ***args, char **type_after,
		char **type_before, t_node **head, t_node **current, t_info *info)
{
	int	count;

	if (strcmp(token, "|") == 0 || is_redirection_cmd(token))
	{
		if (!handle_special_token(token, args, type_after, type_before, head,
				current, info))
			return (0);
	}
	else
	{
		count = 0;
		while (*args && (*args)[count])
			count++;
		*args = realloc(*args, sizeof(char *) * (count + 2));
		(*args)[count] = ft_strdup(token);
		(*args)[count + 1] = NULL;
	}
	return (1);
}

static int	process_tokens(char **tokens, t_node **head, t_node **current,
		char **type_before, t_info *info)
{
	char	**args;
	char	*type_after;
	int		i;
	int		count;
	args = NULL;
	i = 0;
	while (tokens[i])
	{
		if (strcmp(tokens[i], "|") == 0 || is_redirection_cmd(tokens[i]))
		{
			if (!handle_special_token(tokens[i], &args, &type_after,
					type_before, head, current, info))
				return (0);
		}
		else
		{
			count = 0;
			while (args && args[count])
				count++;
			args = realloc(args, sizeof(char *) * (count + 2));
			args[count] = strdup(tokens[i]);
			args[count + 1] = NULL;
		}
		i++;
	}
	if (args)
		if (!create_last_node(args, *type_before, *head, *current, info))
			return (0);
	return (1);
}

t_node	*nodes_init(char **tokens, t_info *info)
{
	t_node	*head;
	t_node	*current;
	char	*type_before;

	head = NULL, current = NULL;
	type_before = strdup("start");
	if (!process_tokens(tokens, &head, &current, &type_before, info))
	{
		free(type_before);
		return (NULL);
	}
	free(type_before);
	return (head);
}

void	print_nodes(t_node *nodes)
{
	while (nodes)
	{
		printf("Args: ");
		for (int i = 0; nodes->args[i]; i++)
			printf("%s ", nodes->args[i]);
		printf("\nType Before: %s, Type After: %s, is_dir_bilt_cmd: %d\n",
			nodes->type_before, nodes->type_after, nodes->is_dir_bilt_cmd);
		nodes = nodes->next;
	}
}

// Example usage
// int	main(void)
// {
// 	char	*tokens[] = {"ls", "|", "grep", "\"txt\"", ">>", "output.txt", "|",
// 			"cd", "..", "|", "ls", "|", "grep", "\"txt rgegeg rwwfw\"", "<",
// 			"gwg.txt", NULL};
// 	t_node	*nodes;

// 	nodes = nodes_init(tokens);
// 	if (nodes)
// 	{
// 		print_nodes(nodes);
// 		free_nodes(&nodes);
// 	}
// 	return (0);
// }
