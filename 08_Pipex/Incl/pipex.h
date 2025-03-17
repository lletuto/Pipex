/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-tuto <lle-tuto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:21:54 by lle-tuto          #+#    #+#             */
/*   Updated: 2025/03/12 10:37:22 by lle-tuto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft2/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipe
{
	int		cmd_nbr;
	int		fd_in;
	int		fd_out;
	int		error;
	char	**paths;
	int		pipefd[2];

}			t_pipe;

void		free_tab(char ***tab);
char		**quote_filler(char **tab, char *s, char d, int index);
char		**str_filler(char **tab, char *s, char c, int index);
char		**tab_filler(char **tab, char *s, char c, char d);
char		**max_split(char *s, char c, char d);
void		free_all(t_pipe *all);
void		putstr2(char *str);
t_pipe		init_struct(char **argv, int argc, char **env);
char		*find_path(char **env, char *command);

#endif