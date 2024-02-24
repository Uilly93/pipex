/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:31:54 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/24 14:10:31 by wnocchi          ###   ########.fr       */
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

#endif