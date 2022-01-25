/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:41:55 by dirony            #+#    #+#             */
/*   Updated: 2021/12/27 20:30:02 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_child_pipes(t_cmd *cmd)
{
	close(cmd->end[0]);
	if (dup2(cmd->previous->end[0], STDIN_FILENO) < 0)
		perror ("Could not dup2 STDIN");
	if (dup2(cmd->end[1], STDOUT_FILENO) < 0)
		perror ("Could not dup2 STDOUT");
}

void	child_pipex(int *fd, t_cmd *cmd, char **envp)
{
	if (!cmd->previous)
	{
		close(cmd->end[0]);
		if (dup2(fd[0], STDIN_FILENO) < 0)
			perror ("Could not dup2 STDIN");
		if (dup2(cmd->end[1], STDOUT_FILENO) < 0)
			perror ("Could not dup2 STDOUT");
	}
	else if (cmd->next)
		close_child_pipes(cmd);
	else
	{
		if (dup2(cmd->previous->end[0], STDIN_FILENO) < 0)
			perror ("Could not dup2 STDIN");
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			perror ("Could not dup2 STDOUT");
	}
	if (execve(cmd->cmd, cmd->arguments, envp) == -1)
		perror ("Could not execve");
	exit(EXIT_FAILURE);
}

void	close_parent_pipes(t_cmd *iter)
{
	if (!iter->previous)
		close(iter->end[1]);
	else if (iter->next)
	{
		close(iter->end[1]);
		close(iter->previous->end[0]);
	}
	else
		close(iter->previous->end[1]);
}

void	pipex(int *fd, t_cmd *list, char **envp)
{
	int		status;
	pid_t	child;
	t_cmd	*iter;

	iter = list;
	while (iter)
	{
		if (iter->next)
			pipe(iter->end);
		child = fork();
		if (child < 0)
			return (perror("Fork: "));
		if (child == 0)
			child_pipex(fd, iter, envp);
		close_parent_pipes(iter);
		waitpid(child, &status, 0);
		iter = iter->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*list;
	int		fd[2];

	if (argc != 5)
		return (0);
	fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] < 0)
		print_file_error(argv[1]);
	fd[1] = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd[1] < 0)
		print_file_error(argv[argc - 1]);
	list = add_cmd_to_list(argc, argv, envp);
	pipex(fd, list, envp);
	ft_lstclear(&list, fd);
	return (0);
}
