/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:56:55 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/01/22 19:14:47 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

void print_nodes(t_node *node)
{
    while (node)
	{
        if (node->type == 'C')
		{
            printf("Command Node:\n");
            for (int i = 0; node->args[i]; i++) {
                printf("  Arg[%d]: %s\n", i, node->args[i]);
            }
        } else if (node->type == '|')
            printf("Pipe Node\n");
        node = node->next;
    }
}

t_node *create_node(char **args, char type)
{
    t_node *node = malloc(sizeof(t_node));
    if (!node)
	{
		free_nodes(&node);
        return NULL;
	}
    node->args = args;
    node->type = type;
    node->next = NULL;
    return (node);
}

t_node *parse_tokens(char **tokens)
{
    t_node *head = NULL;
    t_node *current = NULL;

    while (*tokens)
	{
        // Handle pipe operator
        if (ft_strchr(*tokens, "|") != NULL)
		{
            t_node *pipe_node = create_node(NULL, '|');
            if (!pipe_node)
                return NULL; // Handle malloc failure
            if (current)
                current->next = pipe_node;
            current = pipe_node;
            if (!head)
                head = current;
            tokens++;
            continue;
        }

        // Handle command
        char **args = collect_command_args(tokens); // Function to get args
        t_node *cmd_node = create_node(args, 'C');
        if (!cmd_node)
            return NULL; // Handle malloc failure
        if (current)
            current->next = cmd_node;
        current = cmd_node;
        if (!head)
            head = current;
        tokens += count_args(args); // Move pointer past the args
    }
    return head;
}


