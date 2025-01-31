
# include "../minishell.h"

void	close_fds_childs(int **fd1, t_info *info)
{
	int	j;

	j = 0;
	while (j < info->str_i + 1)
	{
		if (info->i_childs != j)
			close(fd1[j][0]);
		if (info->i_childs + 1 != j)
			close(fd1[j][1]);
		j++;
	}
	if (info->i_childs == 0 && info->fd_file_r != -1)
		dup2(info->fd_file_r, STDIN_FILENO);
	if (info->fd_file_r != -1)
		close(info->fd_file_r);
}

void	child_execve(int **fd1, char **strs, pid_t *frs, t_info *info)
{
	if (info->is_for_w == 0)
		dup2(fd1[info->i_childs + 1][1], STDOUT_FILENO);
	else
		dup2(info->fd_file_w, STDOUT_FILENO);
	close(fd1[info->i_childs + 1][1]);
	if (info->is_for_w == 1)
		close(info->fd_file_w);
	execve(info->path_commd, strs, info->envp);
	perror(info->path_commd);
	de_allocate(&fd1, &frs, info->str_i);
	free_split(strs, info->i_split);
	free_char(info->path_commd);
	exit(1);
}

void	childs(char **str, int **fd1, pid_t *frs, t_info *info)
{
	char	**strs;

	strs = ft_split_p(str[info->i_childs + info->offset], ' ', info);
	if (!strs)
		return (error_pipe(fd1, -3, info, NULL),
			de_allocate(&fd1, &frs, info->str_i), exit(1));
	get_path_command(strs, info);
	if (!info->path_commd)
	{
		if (info->env_null == 1)
			ft_putstr_fd_p(
				ft_strjoin_p("zsh: command not found: ", strs[0], 0), 2, 2);
		return (error_pipe(fd1, -3, info, strs),
			de_allocate(&fd1, &frs, info->str_i),
			exit(127));
	}
	if (info->i_childs != 0)
		dup2(fd1[info->i_childs][0], STDIN_FILENO);
	close(fd1[info->i_childs][0]);
	if (info->i_childs == info->str_i - 1)
		info->is_for_w = 1;
	child_execve(fd1, strs, frs, info);
	exit(0);
}
int	direct_fun(t_node *node, t_info *info)
{
	if (node->type_before == ">")
		info->fd_file_w = open_file_w(node->args[info->ac - 1]);
	else if (node->type_before == ">>")
		info->fd_file_w = open_file_w_b(node->args[info->ac - 1]);
	else if (node->type_before == "<" || node->type_before == "<<")
		info->offset = init_files(node->args, info);
	if (info->fd_file_w == -1)
	{
		info->is_exit_one = 1;
		return (1);
	}
	return (0);
}

char	*builtins_fun(t_node *node, t_info *info)
{
	char	*result;

	result = NULL;
	if (node->args[0] == "cd")
		result = cd_fun(node->args[1], info);
	else if (node->args[0] == "echo")
	{
		if (node->args[1] == "-n")
			result = echo_n_fun(node->args[2]);
		else
			result = echo_with_line_fun(node->args[1]);
	}
	else if (node->args[0] == "env")
		result = env_fun(node->args[1]);
	else if (node->args[0] == "export")
		export_fun(node->args[1], info);
	else if (node->args[0] == "unset")
		unset_func(node->args[1], info);
	else if (node->args[0] == "pwd")
		result = pwd_fun(info);
	else if (node->args[0] == "exit")
		exit_fun();
	return (result);
}

int	order_execve_fun(t_node *node, int **fd1, pid_t *frs, t_info *info)
{
	info->i_childs = 0;
	if (info->fd_file_r == -1)
		info->i_childs = 1;
	while (node)
	{
		if (node->is_dir_bilt_cmd == 0)
		{
			if (direct_fun(node, info) == 1)
				break ;
		}
		else if (node->is_dir_bilt_cmd == 1)
			builtins_fun(node, info);
		else 
		{
			frs[info->i_childs] = fork();
			if (frs[info->i_childs] == 0)
			{
				close_fds_childs(fd1, info);
				childs(node->args, fd1, frs, info);
			}
			info->i_childs++;
		}
		node = node->next;
	}
}

void	init_childs(char **str, int **fd1, pid_t *frs, t_info *info)
{
	info->i_childs = 0;
	if (info->fd_file_r == -1)
		info->i_childs = 1;
	while (info->i_childs < info->str_i)
	{
		if (info->i_childs == info->str_i -1)
		{
			if (info->offset == 2)
				info->fd_file_w = open_file_w(str[info->ac - 1]);
			else
				info->fd_file_w = open_file_w_b(str[info->ac - 1]);
			if (info->fd_file_w == -1)
			{
				info->is_exit_one = 1;
				break ;
			}
		}
		frs[info->i_childs] = fork();
		if (frs[info->i_childs] == 0)
		{
			close_fds_childs(fd1, info);
			childs(str, fd1, frs, info);
		}
		info->i_childs++;
	}
}

int	my_pipe(char **str, t_info *info)
{
	int		**fd1;
	pid_t	*frs;

	if (info->str_i <= 0)
		return (1);
	allocate_fds(&fd1, &frs, info->str_i);
	info->offset = init_files(str, info);
	info->i_fds = 0;
	while (info->i_fds < info->str_i + 1)
		if (pipe(fd1[info->i_fds++]) == -1)
			return (error_pipe(fd1, --info->i_fds, info, NULL),
				de_allocate(&fd1, &frs, info->str_i), exit(1), 1);
	init_childs(str, fd1, frs, info);
	return (finish_parent(&fd1, &frs, info));
}
