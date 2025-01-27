/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:56:55 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/01/27 17:38:39 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>

t_node *create_node(char **args, char type_before, char type_after)
{
    t_node *node = malloc(sizeof(t_node));
    if (!node)
        return NULL;

    node->args = args;
    node->type_before = type_before;
    node->type_after = type_after;
    node->next = NULL;
    node->is_dir_bilt_cmd = 0; // Default value, update as necessary

    return node;
}

static void free_nodes(t_node **head)
{
    t_node *tmp;

    while (*head)
    {
        tmp = (*head)->next;
        if ((*head)->args)
        {
            for (size_t i = 0; (*head)->args[i]; i++)
                free((*head)->args[i]);
            free((*head)->args);
        }
        free(*head);
        *head = tmp;
    }
}

t_node *nodes_init(char **tokens)
{
    t_node *head = NULL;
    t_node *current = NULL;

    for (size_t i = 0; tokens[i]; i++)
    {
        // Assuming tokens contain commands and types, adjust as necessary
        char **args = malloc(2 * sizeof(char *));
        if (!args)
        {
            free_nodes(&head);
            return NULL;
        }

        args[0] = strdup(tokens[i]);
        args[1] = NULL;

        t_node *new_node = create_node(args, 0, 0); // Default types, modify as needed
        if (!new_node)
        {
            free_nodes(&head);
            return NULL;
        }

        if (!head)
        {
            head = new_node;
            current = head;
        }
        else
        {
            current->next = new_node;
            current = current->next;
        }
    }

    return head;
}

void print_nodes(const t_node *head)
{
    while (head)
    {
        printf("Command: %s\n", head->args[0]);
        printf("Type Before: \"%c\", Type After: \"%c\"\n", head->type_before, head->type_after);
        head = head->next;
    }
}

int main()
{
    char *tokens[] = {"ls", "|", "grep", "text", NULL};

    t_node *nodes = nodes_init(tokens);
    if (!nodes)
    {
        perror("Error initializing nodes");
        return 1;
    }

    print_nodes(nodes);

    free_nodes(&nodes);
    return 0;
}