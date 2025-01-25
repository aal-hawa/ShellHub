
#include "../minishell.h"

void free_nodes(t_node *head)
{
    t_node *temp;
    while (head) {
        temp = head;
        head = head->next;
        if (temp->args) {
            for (int i = 0; temp->args[i]; i++)
                free(temp->args[i]);
            free(temp->args);
        }
        free(temp);
    }
}
