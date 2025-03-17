/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-tuto <lle-tuto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:24:14 by lle-tuto          #+#    #+#             */
/*   Updated: 2025/03/12 11:12:35 by lle-tuto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	first_init(t_pipe *all)
{
	all->fd_out = -1;
	all->fd_in = -1;
	all->paths = NULL;
	all->error = 0;
}

static void	more_init(t_pipe *all, char **argv, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 2;
	all->paths = malloc(sizeof(char *) * all->cmd_nbr);
	if (!all->paths)
	{
		free_all(all);
		exit(EXIT_FAILURE);
	}
	while (i < all->cmd_nbr)
	{
		if (argv[j] == NULL || argv[j][0] == '\0')
		{
			putstr2("zsh: command not found: ");
			all->paths[i] = NULL;
		}
		else
			all->paths[i] = find_path(envp, argv[j]);
		i++;
		j++;
	}
}

static void	infile_init(t_pipe *all, char **argv)
{
	all->fd_in = open(argv[1], O_RDONLY);
	if (all->fd_in < 0)
	{
		perror("zsh ");
		all->error = 1;
		all->fd_in = -1;
		return ;
	}
	if (access(argv[1], R_OK) < 0)
	{
		perror("zsh ");
		all->fd_in = -1;
		all->error = 126;
		return ;
	}
}

t_pipe	init_struct(char **argv, int argc, char **envp)
{
	t_pipe	all;

	all.cmd_nbr = argc - 3;
	first_init(&all);
	all.fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (all.fd_out < 0)
	{
		perror("zsh ");
		all.error = 1;
		all.fd_out = -1;
		return (all);
	}
	if (access(argv[argc - 1], W_OK) < 0)
	{
		perror("zsh ");
		all.fd_out = -1;
		all.error = 126;
		return (all);
	}
	infile_init(&all, argv);
	more_init(&all, argv, envp);
	return (all);
}
