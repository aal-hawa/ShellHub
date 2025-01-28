#include "../minishell.h"

static int is_redirection_cmd(const char *cmd)
{
    int i;
    const char *redirections[] = {">", "<", ">>", "<<", NULL};
    for (i = 0; redirections[i]; i++)
    {
        if (ft_strcmp(cmd, redirections[i]) == 0)
            return 1;
    }
    return 0;
}

static int is_builtin_cmd(const char *cmd)
{
    int i;
    const char *builtins[] = {"cd", "pwd", "echo", "export", "unset", "env", "exit", NULL};
    for (i = 0; builtins[i]; i++)
    {
        if (ft_strcmp(cmd, builtins[i]) == 0)
            return 1;
    }
    return 0;
}

t_node *create_node(char **args, const char *type_before, const char *type_after)
{
    t_node *node = malloc(sizeof(t_node));
    if (!node)
        return NULL;
    node->args = args;
    node->type_before = type_before ? ft_strdup(type_before) : NULL;
    node->type_after = type_after ? ft_strdup(type_after) : NULL;
    node->next = NULL;
    node->is_dir_bilt_cmd = is_builtin_cmd(args[0]) ? 1 : is_redirection_cmd(type_before) ? 0 : 2;
    return node;
}

t_node *nodes_init(char **tokens)
{
    t_node *head = NULL, *current = NULL;
    char **args = NULL;
    char *type_before = ft_strdup("start");
    char *type_after = NULL;

    for (int i = 0; tokens[i]; i++)
    {
        if (ft_strcmp(tokens[i], "|") == 0 || is_redirection_cmd(tokens[i]))
        {
            type_after = ft_strdup(tokens[i]);
            if (args)
            {
                t_node *new_node = create_node(args, type_before, type_after);
                if (!new_node)
                {
                    free(type_before);
                    free(type_after);
                    free_nodes(&head);
                    return NULL;
                }
                if (!head)
                    head = new_node;
                else
                    current->next = new_node;
                current = new_node;
                args = NULL;
            }
            free(type_before);
            type_before = type_after;
            type_after = NULL;
        }
        else
        {
            int count = 0;
            while (args && args[count])
                count++;
            args = realloc(args, sizeof(char *) * (count + 2));
            args[count] = ft_strdup(tokens[i]);
            args[count + 1] = NULL;
        }
    }

    if (args)
    {
        t_node *new_node = create_node(args, type_before, "end");
        if (!new_node)
        {
            free(type_before);
            free_nodes(&head);
            return NULL;
        }
        if (!head)
            head = new_node;
        else
            current->next = new_node;
    }
    free(type_before);
    return head;
}

void print_nodes(t_node *nodes)
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
int main()
{
    char *tokens[] = {"ls", "|", "grep", "\"txt\"", ">>", "output.txt", "|", "cd", "..", "|", "ls", "|", "grep", "\"txt rgegeg rwwfw\"", "<", "gwg.txt", NULL};
    t_node *nodes = nodes_init(tokens);

    if (nodes)
    {
        print_nodes(nodes);
        free_nodes(&nodes);
    }
    return 0;
}
