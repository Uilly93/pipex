/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:24:28 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/21 17:01:52 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

// int pipex(int file1, char *cmd1, char *cmd2, int file2)
// {
// 	file1 = fopen(file1, O_RDONLY)
// }

char **get_path(char **envp)
{
	int i;
	char **res;

	i = 0;
	res = NULL;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			return(res = ft_split(envp[i], ':'));
				if (!res)
					return (NULL);
		}
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
			return(res);
		// free(res);
		i++;
	}
	return (NULL);
}

int main(int ac, char **av, char **envp)
{
	// t_pipe *pipe;
	(void)ac;
	(void)av;

	pid_t pid;
	// pid_t pid2;
	char	*res;
	// char	*res2;

	pid = fork();
	// pid2 = fork();
	
	// ft_printf("pid1 = %d\n", pid);
	if(pid == -1)
	{
		perror("fork");
		exit(1);
	}

	res = join_path_access(av[1], envp);
	// ft_printf("res: %s\n", res);
	// res2 = join_path_access(av[2], envp);
	// ft_printf("res2: %s\n", res2);
	// execve(res, &av[1], envp);
	// free(res);
	// pipe->file1 = av[1];
	// pipe->cmd1 = av[2];
	// pipe->cmd2 = av[3];
	// pipe->file2 = av[4];
	
	// if (ac == 5){
	// 	if(access(pipe->file1, F_OK | W_OK | R_OK | X_OK) == 0)
	// 		open(pipe->file1, O_RDONLY);
	if(pid == 0){
		execve(res, &av[1], envp);
	}
	// waitpid(pid, NULL, 0);
	// if(pid2 == 0){
	// 	execve(res2, &av[2], envp);
	// }
	// waitpid(pid2, NULL, 0);
	// ft_printf("%s\n", "salut");
	// for (int i = 0; envp[0]; i++)
	return(0);
}
