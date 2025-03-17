/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-tuto <lle-tuto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:02:47 by lle-tuto          #+#    #+#             */
/*   Updated: 2025/03/12 10:33:33 by lle-tuto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count(char *s, int *quote, int *words, int i)
{
	char	c;
	char	d;

	d = '\'';
	c = ' ';
	(*quote) = 1;
	i++;
	if (s[i])
		(*words)++;
	while (s[i] && s[i] != d)
		i++;
	if (s[i] == d)
		(*quote) = 0;
	return (i);
}

static int	count_words(char *s, char c, char d)
{
	int	i;
	int	words;
	int	quote;

	i = 0;
	words = 0;
	quote = 0;
	while (s[i])
	{
		if (s[i] == d && quote == 0)
			i = count(s, &quote, &words, i);
		else if (s[i] != c)
		{
			words++;
			while (s[i] && s[i] != c && s[i] != d)
				i++;
		}
		else
			i++;
	}
	return (words);
}

char	**str_filler(char **tab, char *s, char c, int index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((s[i] != c) && s[i])
		i++;
	tab[index] = malloc(sizeof(char) * (i + 1));
	if (!tab[index])
	{
		while (j < index)
		{
			free(tab[j]);
			j++;
		}
		return (NULL);
	}
	i = 0;
	while ((s[i] != c) && s[i])
	{
		tab[index][i] = s[i];
		i++;
	}
	tab[index][i] = '\0';
	return (tab);
}

char	**quote_filler(char **tab, char *s, char d, int index)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while ((s[i] != d) && s[i])
		i++;
	tab[index] = malloc(sizeof(char) * (i + 1));
	if (!tab[index])
	{
		while (j < index)
		{
			free(tab[j]);
			j++;
		}
		return (NULL);
	}
	j = 0;
	while (j < (i - 1))
	{
		tab[index][j] = s[j + 1];
		j++;
	}
	tab[index][j] = '\0';
	return (tab);
}

char	**max_split(char *s, char c, char d)
{
	int		size;
	char	**tab;

	if (!s)
		return (NULL);
	size = count_words(s, c, d);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	if (!tab_filler(tab, s, c, d))
	{
		free(tab);
		return (NULL);
	}
	return (tab);
}
