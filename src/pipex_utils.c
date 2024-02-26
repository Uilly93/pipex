/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:48:39 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/26 13:31:06 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_tabs(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i])
			free(s[i++]);
	}
	if (s)
		free(s);
}

char	**get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			return (ft_split(envp[i], ':'));
		else
			i++;
	}
	return (NULL);
}

char	*join_path_access(char *av, char **envp)
{
	int		i;
	char	**s;
	char	*res;

	i = 0;
	res = NULL;
	s = get_path(envp);
	if (!s)
		return (write(2, "Error: no environment\n", 22), NULL);
	while (s[i])
	{
		res = ft_strcat_malloc(s[i], "/");
		if (!res)
			return (NULL);
		res = join_free(res, av);
		if (!res)
			return (NULL);
		if (access(res, X_OK) == 0)
			return (free_tabs(s), res);
		free(res);
		i++;
	}
	free_tabs(s);
	return (NULL);
}

void	free_close(t_pipex *pipex)
{
	if (pipex->cmd1)
		free_tabs(pipex->cmd1);
	if (pipex->cmd2)
		free_tabs(pipex->cmd2);
	if (pipex->path1)
		free(pipex->path1);
	if (pipex->path2)
		free(pipex->path2);
	if (pipex->in != -1)
		close(pipex->in);
	if (pipex->out != -1)
		close(pipex->out);
	close(pipex->pipein[0]);
	close(pipex->pipein[1]);
}

void	close_fds(t_pipex pipex)
{
	if (pipex.in != -1)
		close(pipex.in);
	if (pipex.out != -1)
		close(pipex.out);
	close(pipex.pipein[0]);
	close(pipex.pipein[1]);
}
