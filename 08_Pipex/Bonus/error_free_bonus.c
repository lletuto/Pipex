/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-tuto <lle-tuto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:28:15 by lle-tuto          #+#    #+#             */
/*   Updated: 2025/03/11 14:28:51 by lle-tuto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	putstr2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}

void	free_paths(char ***paths, t_pipe *all)
{
	int	i;

	i = 0;
	if (!(*paths) || !paths)
		return ;
	while (i < all->cmd_nbr)
	{
		free((*paths)[i]);
		i++;
	}
	free(*paths);
	*paths = NULL;
}

void	free_tab(char ***tab)
{
	int	i;

	i = 0;
	if (!(*tab) || !tab)
		return ;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		i++;
	}
	free(*tab);
	*tab = NULL;
}

void	free_all(t_pipe *all)
{
	if (all->paths)
		free_paths(&all->paths, all);
	if (all->fd_in != -1)
	{
		close(all->fd_in);
		all->fd_in = -1;
	}
	if (all->fd_out != -1)
	{
		close(all->fd_out);
		all->fd_out = -1;
	}
}
