#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_node
{
	char			**args;
	char			*type_before;
	char			*type_after;
	struct s_node	*next;
	int				is_dir_bilt_cmd;
}					t_node;

char	**ft_split(char const *s, char c);



static t_node *get_nodes(char *line)
{
	t_node *node;
	t_node *first_node;
	int i;
	int j;

	j = 0;
	i = 0;
	node = malloc(sizeof(t_node));
	first_node = node;
	if (!node)
		return (NULL);
	node->type_before = strdup("start");
	while (line[i])
	{
		if(line[i] == '|' || line[i] == '>' || line[i] == '<')
		{
			if(line[i] != '|')
			{
				if(line[i] == '>' && line[i + 1] == '>')
				{
					node->type_after == strdup(">>");
				}
				else if (line[i] == '<' && line[i + 1] == '<')
				{
					node->type_after == strdup("<<");
				}
				else
				{
					node->type_after = strdup(line[i]);
				}
			}
			else
			{
				node->type_after = strdup(line[i]);
			}
			char *cmd_order = malloc(sizeof(char) * (i - j + 1));
			while (j < i)
			{
				cmd_order[j] = line[j];
				j++;
			}
			cmd_order[j] = '\0';
			node->args = ft_split(cmd_order, ' ');
			
		}
		i++;
	}
}

t_node *new_node(char *line)
{
	t_node *nodes;

	nodes = get_tokens(line);

}
// ls | grep	r00