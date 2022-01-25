/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:42:48 by dirony            #+#    #+#             */
/*   Updated: 2021/12/27 20:17:36 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdio.h> 

typedef struct s_cmd
{
	int				end[2];
	char			*cmd;
	char			**arguments;
	int				here_doc;
	char			*limiter;
	struct s_cmd	*previous;
	struct s_cmd	*next;
}	t_cmd;

char	*get_cmd_name(char *cmd);
char	*get_cmd_path(char *cmd, char **envp);
char	*find_cmd_path(char *cmd, char *path);
t_cmd	*add_cmd_to_list(int argc, char **argv, char **envp);

char	**ft_split(char const *s, char ch);
size_t	ft_strlen(const char *str);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(char *s, char ch);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *str);

void	ft_lstadd_back(t_cmd **list, t_cmd *new_elem);
t_cmd	*ft_lstnew(char *argv, char **envp);
int		ft_lstsize(t_cmd *list);
void	ft_lstclear(t_cmd **list, int *fd);

void	print_file_error(char *file_name);
void	print_cmd_error(char *argv);

#endif
