/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:24:28 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/26 11:10:33 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	creat_child1(t_pipex *pipex, char **envp)
{
	pipex->path1 = join_path_access(pipex->cmd1[0], envp);
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
		return (perror(""), 1);
	if (pipex->pid1 == 0)
	{
		close(pipex->out);
		close(pipex->pipein[0]);
		dup2(pipex->in, STDIN_FILENO);
		dup2(pipex->pipein[1], STDOUT_FILENO);
		close(pipex->pipein[1]);
		close(pipex->in);
		if (execve(pipex->path1, pipex->cmd1, envp) == -1)
			perror("Error");
		free_close(pipex);
		exit(0);
	}
	return (0);
}

int	creat_child2(t_pipex *pipex, char **envp)
{
	pipex->path2 = join_path_access(pipex->cmd2[0], envp);
	pipex->pid2 = fork();
	if (pipex->pid2 == -1)
		return (perror(""), 1);
	if (pipex->pid2 == 0)
	{
		close(pipex->in);
		close(pipex->pipein[1]);
		dup2(pipex->pipein[0], STDIN_FILENO);
		dup2(pipex->out, STDOUT_FILENO);
		close(pipex->pipein[0]);
		close(pipex->out);
		if (execve(pipex->path2, pipex->cmd2, envp) == -1)
			perror("Error");
		free_close(pipex);
		exit(0);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
		return (write(2, "Error: program need 4 arguments\n", 32), 1);
	bzero(&pipex, sizeof(pipex));
	if (pipex.in == -1)
		perror(av[1]);
	pipex.out = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex.out == -1)
		return (perror(av[4]), 1);
	pipe(pipex.pipein);
	pipex.cmd1 = ft_split(av[2], ' ');
	pipex.cmd2 = ft_split(av[3], ' ');
	if (!pipex.cmd1 || !pipex.cmd2)
		return (1);
	pipex.in = open(av[1], O_RDONLY);
	if (creat_child1(&pipex, envp))
		return (1);
	if (creat_child2(&pipex, envp))
		return (1);
	free_close(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return (0);
}
