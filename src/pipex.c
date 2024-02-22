/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:24:28 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/22 16:20:17 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
// #include <stdio.h>
// #include <unistd.h>
// #include <stdio.h>

// int pipex(int file1, char *cmd1, char *cmd2, int file2)
// {
// 	file1 = fopen(file1, O_RDONLY)
// }

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
	// free(res);
	return (NULL);
}

// int	create_fork()

int main(int ac, char **av, char **envp)
{
	// t_pipe *pipe;
	(void)ac;
	// (void)av;
	int out;
	int in;
	pid_t pid;
	int	pipein[2];
	pid_t pid2;
	char	*res;
	char	*res2;

	char **cmd1;
	char **cmd2;

	cmd1 = NULL;
	cmd2 = NULL;
	cmd1 = ft_split(av[2], ' ');
	cmd2 = ft_split(av[3], ' ');
	pipe(pipein);
	res = join_path_access(av[2], envp);
	res2 = join_path_access(av[3], envp);
	// ft_printf("res2:%s\n", res2);
	// ft_printf("res:%s\n", res);
	in = open(av[1], O_RDONLY);
	// if(in == -1)
	// 	perror("");
	out = open(av[4], O_CREAT | O_WRONLY , 0644);
	// ft_printf("%d\n", out);
	// ft_printf("%d\n", in);
	// ft_printf("pid1 = %d\n", pid);
	// execve(res, &av[1], envp);
	// free(res);
	// pipe->file1 = av[1];
	// pipe->cmd1 = av[2];
	// pipe->cmd2 = av[3];
	// pipe->file2 = av[4];
	
	// if (ac == 5){
	// 	if(access(pipe->file1, F_OK | W_OK | R_OK | X_OK) == 0)
	// 		open(pipe->file1, O_RDONLY);
	pid = fork();
	if(pid == -1)
		perror("");
	if(pid == 0){
		dup2(in, STDIN_FILENO);
		dup2(pipein[1], 1);
		close(pipein[0]);
		 if (execve(res, cmd1, envp) == -1)
		 	perror("");
		exit(0);
		free(res);
	}
	pid2 = fork();
	if(pid2 == -1)
		perror("");
	if(pid2 == 0)
	{
		dup2(pipein[1], 0);
		dup2(out, STDOUT_FILENO);
		close(pipein[0]);
		execve(res2, cmd2, envp);
		exit(0);
		free(res2);
	}
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	// ft_printf("%p\n", res);
	// if(pid2 == 0){
	// 	execve(res2, &av[2], envp);
	// }
	// waitpid(pid2, NULL, 0);
	// ft_printf("%s\n", "salut");
	// for (int i = 0; envp[0]; i++)
	return(0);
}
