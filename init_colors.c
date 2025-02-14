#include "minishell.h"

void	init_colors(t_colors *colors, t_info *info)
{
	colors->default_color = "\033[0m";
	colors->red_color = "\033[1;31m";
	colors->green_color = "\033[1;32m";
	colors->yellow_color = "\033[1;33m";
	colors->blue_color = "\033[1;34m";
	colors->magenta_color = "\033[1;35m";
	colors->cyan_color = "\033[1;36m";
	colors->white_color = "\033[1;37m";
	info->colors = colors;
}