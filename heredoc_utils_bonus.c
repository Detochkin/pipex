/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 15:57:12 by dirony            #+#    #+#             */
/*   Updated: 2021/12/27 20:07:04 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pipe_for_heredoc(t_cmd *iter, int *fd)
{
	int		status;
	pid_t	child;
	int		end[2];

	pipe(end);
	child = fork();
	if (child < 0)
		return (perror("Fork: "));
	if (child == 0)
		read_from_heredoc(iter, end);
	close(end[1]);
	waitpid(child, &status, 0);
	*fd = end[0];
}

void	print_prompt_string(t_cmd *cmd)
{
	int	i;
	int	pipes_num;

	pipes_num = ft_lstsize(cmd);
	i = 0;
	while (i < pipes_num - 1)
	{
		ft_putstr_fd("pipe ", 1);
		i++;
	}
	ft_putstr_fd("heredoc> ", 1);
}

int	read_from_heredoc(t_cmd *cmd, int *end)
{
	char	*buff;
	char	*limiter;
	char	*temp;
	int		lim_len;

	close(end[0]);
	limiter = ft_strjoin(cmd->limiter, "\n");
	lim_len = ft_strlen(limiter);
	print_prompt_string(cmd);
	buff = get_next_line(0);
	while (ft_strncmp(buff, limiter, lim_len) != 0)
	{
		temp = buff;
		ft_putstr_fd(buff, end[1]);
		print_prompt_string(cmd);
		buff = get_next_line(0);
		free(temp);
	}
	free(buff);
	free(limiter);
	exit(EXIT_SUCCESS);
}

int	parse_heredoc(char **argv, t_cmd *cmd)
{
	cmd->here_doc = 1;
	cmd->limiter = argv[2];
	return (0);
}
