/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-tuto <lle-tuto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:31:26 by lle-tuto          #+#    #+#             */
/*   Updated: 2025/03/12 10:34:33 by lle-tuto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	lines(char *s, int i, int *index, char d)
{
	(*index)++;
	i++;
	while (s[i] && s[i] != d)
		i++;
	if (s[i] == d)
		i++;
	return (i);
}

static int	lines_again(char *s, int i, int *index, char c)
{
	(*index)++;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**tab_filler(char **tab, char *s, char c, char d)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (s[i])
	{
		if (s[i] == d)
		{
			if (!quote_filler(tab, &s[i], d, index))
				return (NULL);
			i = lines(s, i, &index, d);
		}
		if (s[i] != c && s[i])
		{
			if (!str_filler(tab, &s[i], c, index))
				return (NULL);
			i = lines_again(s, i, &index, c);
		}
		if (s[i] == c && s[i])
			i++;
	}
	tab[index] = 0;
	return (tab);
}
