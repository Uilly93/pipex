/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:24:28 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/24 16:11:16 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <strings.h>
#include <unistd.h>

void	free_tabs(char **s)
{
	int i;

	i = 0;
	while(s[i])
		free(s[i++]);
	free(s);
}

char **get_path(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			return(ft_split(envp[i], ':'));
		else
			i++;
	}
	return (NULL);
}

char	*join_path_access(char *av, char **envp)
{
	int i = 0;
	char **s;
	char *res;
	
	res = NULL;
	s = get_path(envp);
	if(!s)
		return (NULL);
	while(s[i])
	{
		res = ft_strcat_malloc(s[i], "/");
		res = join_free(res, av);
		if(access(res, X_OK) == 0)
		{
			free_tabs(s);
			return(res);
		}
		free(res);
		i++;
	}
	free_tabs(s);
	return (NULL);
}

void	free_cmd_path(t_pipex *pipex)
{
	if (pipex->cmd1)
		free_tabs(pipex->cmd1);
	if (pipex->cmd2)
		free_tabs(pipex->cmd2);
	if (pipex->path1)
		free(pipex->path1);
	if (pipex->path2)
		free(pipex->path2);
}

// int	exec_child1(pid_t child1, int *pipein[2], )
// {
// 	if(child1 == 0)
// 	{
// 		close(pipein[0]);
// 		dup2(in, STDIN_FILENO);
// 		dup2(pipein[1], STDOUT_FILENO);
// 		 if (execve(res, cmd1, envp) == -1)
// 		 	perror("");
// 		close(in);
// 		close(out);
// 		close(pipein[1]);
// 		free_tabs(cmd1);
// 		free_tabs(cmd2);
// 		free(res);
// 		exit(0);
// 	}
// }

// int	create_fork()
void	close_fds(t_pipex pipex)
{
	close(pipex.in);
	close(pipex.out);
	close(pipex.pipein[0]);
	close(pipex.pipein[1]);
}

int	creat_child1(t_pipex *pipex, char **envp)
{
	pipex->pid1 = fork();
	if(pipex->pid1 == -1)
		return(perror(""), 1);
	if(pipex->pid1 == 0)
	{
		close(pipex->out);
		close(pipex->pipein[0]);
		dup2(pipex->in, STDIN_FILENO);
		dup2(pipex->pipein[1], STDOUT_FILENO);
		close(pipex->pipein[1]);
		close(pipex->in);
		 if (execve(pipex->path1, pipex->cmd1, envp) == -1)
		 	perror("");
		free_cmd_path(pipex);
		exit(0);
	}
	return(0);
}

int	creat_child2(t_pipex *pipex, char **envp)
{
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
            perror("");
		free_cmd_path(pipex);
		exit(0);
	}
	return (0);
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	t_pipex pipex;

	if(ac != 5)
		return(write(2, "program need 4 arguments\n", 25), 1);
	bzero(&pipex, sizeof(pipex));
	if(pipex.in == -1)
		perror(av[1]);
	pipex.out = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(pipex.out == -1)
		return(perror(av[4]), 1);
	pipex.cmd1 = ft_split(av[2], ' ');
	pipex.cmd2 = ft_split(av[3], ' ');
	pipe(pipex.pipein);
	pipex.path1 = join_path_access(pipex.cmd1[0], envp);
	pipex.path2 = join_path_access(pipex.cmd2[0], envp);
	pipex.in = open(av[1], O_RDONLY);
	creat_child1(&pipex, envp);
	creat_child2(&pipex, envp);
	// pipex.pid1 = fork();
	// if(pipex.pid1 == -1)
	// 	perror("");
	// if(pipex.pid1 == 0)
	// {
	// 	close(pipex.out);
	// 	close(pipex.pipein[0]);
	// 	dup2(pipex.in, STDIN_FILENO);
	// 	dup2(pipex.pipein[1], STDOUT_FILENO);
	// 	close(pipex.pipein[1]);
	// 	close(pipex.in);
	// 	 if (execve(pipex.path1, pipex.cmd1, envp) == -1)
	// 	 	perror("");
	// 	free_cmd_path(&pipex);
	// 	exit(0);
	// }
	// pipex.pid2 = fork();
	// if (pipex.pid2 == -1)
	// 	return (perror(""), 1);
	// if (pipex.pid2 == 0)
	// {
	// 	close(pipex.in);
	// 	close(pipex.pipein[1]);
	// 	dup2(pipex.pipein[0], STDIN_FILENO);
	// 	dup2(pipex.out, STDOUT_FILENO);
	// 	close(pipex.pipein[0]);
	// 	close(pipex.out);
	// 	if (execve(pipex.path2, pipex.cmd2, envp) == -1)
    //         perror("");
	// 	free_cmd_path(&pipex);
	// 	exit(0);
	// }
	close(pipex.in);
	close(pipex.out);
	close(pipex.pipein[0]);
	close(pipex.pipein[1]);
	free_cmd_path(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return(0);
}
