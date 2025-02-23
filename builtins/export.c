/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:45:13 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/02/22 20:18:28 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int check_valid_alpha_(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}

int check_valid_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int check_is_valid(char *str)
{
	int i = 1;

	if (!str || str[0] == '\0' || !check_valid_alpha_(str[0]))
		return (0);
	while (str[i])
	{
		if (!(check_valid_alpha_(str[i]) || check_valid_num(str[i]) || str[i] == '='))
			return (0);
		i++;
	}
	return (1);
}

//export hello from 42AD We @re So H@ppy here live here=everything USER

int is_has_equal(char *str)
{
	while(*str)
	{
		if(*str == '=')
			return(1);
		str++;
	}
	return (0);
}

// void add_double_qout(char *str)
// {
// 	int len = ft_strlen(str);
// 	char *new_str = malloc(sizeof(char) * len + 3);
	
// }

void check_and_add(t_info *info, char *arg, int add_to_env)
{
	(void) add_to_env;
	
	if(is_exist_str_in_2array(info->export, arg, 0) || is_exist_str_in_2array(info->export, arg, ft_strlen(arg)))
	{
		printf("\n------\ndeleting {{%s}}, adding with new value{{%s}}\n------\n", arg, arg);
	}
	else
	{
		printf("\n------\nadding{{%s}}\n------\n",arg);
	}
}

int ft_strnlen(char *s, char c)
{
	int i = 0;
	while (s[i] && s[i] != c)
		i++;
	return(i + 1);
}

char	**export_fun(char **args, t_info *info, int is_print)
{
	int i = 1;
	//delete (void) when create the function
	(void)is_print;
	if (!info)
		return (NULL);
    if(!args[i])
		print_array2d(info->export, 1);
	else
	{
		while (args[i])
		{
			if(is_has_equal(args[i]))
			{
				if(check_is_valid(ft_strccpy(args[i], '=')))
					printf("valid key= %s\n", ft_strccpy(args[i], '='));
				else
					printf("Invalid key= %s\n", ft_strccpy(args[i], '='));
				printf("value= %s\n", ft_strchr(args[i], '='));
				// printf("char len till the = is %d\n", ft_strnlen(args[i], '='));
			} else
				printf("key %s\n", args[i]);
			// else
			// 	chack valid 
			i++;
		}
		
	}

	return (NULL);
}


/*
get the arguments like now, check if it's include = or not, if it's not just add in export, if include save in env, then send these to split on first = then add it in export
after that export will be totally ready
-------
go to unset feature, and use the same function to search exist or not
*/

/*
**********Don't forget to check if the validation functon working to check just the key, or the key and the value******
for example, if I write export v@r=12, it will be invalid, but If I did export var=v@r it will be valid
*/

/*
also don't forget to check if the export print, because it's a little bit different from env in the begining of every line
*/