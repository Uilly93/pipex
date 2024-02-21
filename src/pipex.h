/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:31:54 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/21 10:44:59 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "../libft/libft.h"

typedef struct s_pipe
{
	char	*file1;
	char	*cmd1;
	char	*cmd2;
	char	*file2;

}	t_pipe;

#endif