/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:31:54 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/26 10:51:49 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "../libft/libft.h"

typedef struct s_pipex
{
	int		in;
	int		out;
	char	*path1;
	char	*path2;
	char	**cmd1;
	char	**cmd2;
	pid_t	pid1;
	pid_t	pid2;
	int		pipein[2];

}	t_pipex;

void	free_tabs(char **s);
char	**get_path(char **envp);
char	*join_path_access(char *av, char **envp);
void	free_close(t_pipex *pipex);
void	close_fds(t_pipex pipex);
int		creat_child1(t_pipex *pipex, char **envp);
int		creat_child2(t_pipex *pipex, char **envp);

#endif