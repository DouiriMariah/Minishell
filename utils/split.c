/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 05:00:16 by mdouiri           #+#    #+#             */
/*   Updated: 2022/07/21 05:00:17 by mdouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

extern int	g_ret_val;

char	*ft_strdup_split( char *src, int start, int end)
{
	int		i;
	int		j;
	char	*cpy;

	j = 0;
	i = start;
	cpy = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!(cpy))
		return (NULL);
	while (src[i] && i < end)
	{
		cpy[j] = (char)src[i];
		i++;
		j++;
	}
	cpy[j] = '\0';
	return (cpy);
}

static int	total_len(char *s, char c)
{
	int	i;
	int	mots;

	i = 0;
	mots = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		mots++;
		while (s[i] != c && s[i])
			i++;
		while (s[i] == c && s[i])
			i++;
	}
	return (mots);
}

char	**ft_split(char *s, char c)
{
	char	**split;
	int		k;
	int		j;
	int		i;

	k = 0;
	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (total_len((char *)s, c) + 1));
	if (!(split))
		return (NULL);
	i = 0;
	while (s[i] && k < total_len((char *)s, c))
	{
		while (s[i] == c && s[i])
			i++;
		j = i;
		while (s[i] != c && s[i])
			i++;
		split[k++] = ft_strdup_split(s, j, i);
	}
	split[k] = 0;
	return (split);
}
