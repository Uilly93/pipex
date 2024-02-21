/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:24:28 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/21 14:58:54 by wnocchi          ###   ########.fr       */
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

char	**join_path(char *av, char **envp)
{
	int i = 0;
	char **s;
	
	s = get_path(envp);
	while(s[i])
	{
		s[i] = join_free(s[i], "/");
		s[i] = join_free(s[i], av);
		i++;
	}
	return (s);
}

int	try_access(char **s)
{
	
}

int main(int ac, char **av, char **envp)
{
	// t_pipe *pipe;
	(void)ac;
	(void)av;

	// pid_t pid;
	
	char	**res;

	res = join_path(av[1], envp);
	for(int i = 0;res[i];i++){
		ft_printf("%s\n", res[i]);
		free(res[i]);	
	}
	if(res)
		free(res);
	// pid = fork();
	// if(pid == -1)
	// {
	// 	perror("fork");
	// 	exit(1);
	// }
	// pipe->file1 = av[1];
	// pipe->cmd1 = av[2];
	// pipe->cmd2 = av[3];
	// pipe->file2 = av[4];
	
	// if (ac == 5){
	// 	if(access(pipe->file1, F_OK | W_OK | R_OK | X_OK) == 0)
	// 		open(pipe->file1, O_RDONLY);
	// if(pid == 0){
		
	// 	execve("/usr/bin/ls", av, envp);
	// }
	// else {
	// 	waitpid(pid, NULL, 0);
	// }
	// ft_printf("%s\n", "salut");
	// }
	// for (int i = 0; envp[0]; i++)
	return(0);
}
