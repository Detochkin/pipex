/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 16:05:23 by dirony            #+#    #+#             */
/*   Updated: 2021/12/25 16:05:25 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

void	print_file_error(char *file_name)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd("\n", 2);
	exit (EXIT_FAILURE);
}

void	print_cmd_error(char *argv)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putstr_fd(get_cmd_name(argv), 2);
	ft_putstr_fd("\n", 2);
	exit (EXIT_FAILURE);
}
