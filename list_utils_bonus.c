/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 19:45:15 by dirony            #+#    #+#             */
/*   Updated: 2021/12/27 20:17:08 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_lstclear(t_cmd **list, int *fd)
{
	t_cmd	*temp;
	t_cmd	*iter;
	int		i;

	iter = *list;
	while (iter)
	{
		temp = iter->next;
		free(iter->cmd);
		if (iter->arguments)
		{
			i = 0;
			while (iter->arguments[i])
				free(iter->arguments[i++]);
		}
		free(iter->arguments);
		free(iter);
		iter = temp;
	}
	*list = NULL;
	close(fd[0]);
	close(fd[1]);
}

void	ft_lstadd_back(t_cmd **list, t_cmd *new_elem)
{
	t_cmd	*iterator;

	iterator = *list;
	if (*list)
	{
		while (iterator->next)
			iterator = iterator->next;
		iterator->next = new_elem;
		if (new_elem)
			new_elem->previous = iterator;
	}
	else
		*list = new_elem;
}

t_cmd	*ft_lstnew(char *argv, char **envp)
{
	t_cmd	*new_elem;

	new_elem = malloc(sizeof(t_cmd));
	if (NULL == new_elem)
		return (NULL);
	new_elem->next = NULL;
	new_elem->previous = NULL;
	new_elem->here_doc = 0;
	new_elem->cmd = get_cmd_path(argv, envp);
	if (!new_elem->cmd)
		print_cmd_error(argv);
	new_elem->arguments = ft_split(argv, ' ');
	new_elem->end[0] = 0;
	new_elem->end[1] = 0;
	return (new_elem);
}

t_cmd	*add_cmd_to_list(int argc, char **argv, char **envp, int flag)
{
	int		i;
	t_cmd	*new_elem;
	t_cmd	*list;
	char	*temp;

	i = flag + 2;
	new_elem = NULL;
	list = ft_lstnew(argv[i], envp);
	if (flag)
		parse_heredoc(argv, list);
	while (++i < argc - 1)
	{
		temp = get_cmd_path(argv[i], envp);
		if (temp)
		{	
			new_elem = ft_lstnew(argv[i], envp);
			ft_lstadd_back(&list, new_elem);
		}
		else
			print_cmd_error(argv[i]);
		free(temp);
	}
	return (list);
}

int	ft_lstsize(t_cmd *list)
{
	int	count;

	count = 0;
	while (list)
	{
		count++;
		list = list->next;
	}
	return (count);
}
