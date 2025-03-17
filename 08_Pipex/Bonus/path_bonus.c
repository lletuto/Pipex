/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-tuto <lle-tuto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:29:22 by lle-tuto          #+#    #+#             */
/*   Updated: 2025/03/12 11:34:48 by lle-tuto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*make_it(char **tab, char **tab_new)
{
	int		i;
	char	*new;
	char	*tmp;

	i = 0;
	while (tab[i])
	{
		tmp = ft_strjoin(tab[i], "/");
		new = ft_strjoin(tmp, tab_new[0]);
		free(tmp);
		tmp = NULL;
		if (access(new, X_OK) == 0)
			break ;
		free(new);
		new = NULL;
		i++;
	}
	if (tab[i] == NULL)
		return (NULL);
	return (new);
}

static char	*find_lign(char *path, char *command)
{
	char	**tab;
	char	**tab_new;
	char	*new;

	tab_new = NULL;
	tab = NULL;
	tab = ft_split(path, ':');
	if (!tab)
		return (NULL);
	tab_new = ft_split(command, ' ');
	if (!tab_new)
	{
		free_tab(&tab);
		return (NULL);
	}
	new = make_it(tab, tab_new);
	if (!new)
	{
		putstr2("zsh: command not found: ");
		putstr2(tab_new[0]);
		putstr2("\n");
	}
	free_tab(&tab);
	free_tab(&tab_new);
	return (new);
}

char	*find_path(char **envp, char *command)
{
	int		i;
	char	*test;
	char	*path;

	i = 0;
	path = NULL;
	test = NULL;
	while (envp[i] && !test)
	{
		test = ft_strnstr(envp[i], "PATH=", 5);
		i++;
	}
	if (!test)
		return (NULL);
	path = find_lign(test, command);
	return (path);
}
