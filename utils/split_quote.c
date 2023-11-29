/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 05:00:23 by mdouiri           #+#    #+#             */
/*   Updated: 2022/08/22 04:20:29 by amattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

extern int	g_ret_val;

char	*ft_strdup_split_dans_process( char *src, int start, int end)
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
		if ((src[start] == '\"' || src[start] == '\'') && src[i] == '\t')
			cpy[j] = ' ';
		else
			cpy[j] = (char)src[i];
		i++;
		j++;
	}
	cpy[j] = '\0';
	return (cpy);
}

int	not_in_quote(char *s, char c, int i)
{
	if (!s)
		return (i);
	while (s[i] && s[i] != c)
	{
		if (chevron(s[i]))
		{
			i++;
			if (s[i] && chevron(s[i]))
				i++;
			if (c != '|')
				break ;
		}
		while (s[i] && (s[i] == '\'' || s[i] == '\"'))
			quote(s, &i);
		if (s[i] && s[i] != c && !chevron(s[i]))
			i++;
		if (s[i] && c != '|' && chevron(s[i]))
			break ;
	}
	return (i);
}

int	total_len_dans_process(char *s, char c)
{
	int	i;
	int	mots;

	i = 0;
	mots = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] == c)
		i++;
	while (s && s[i])
	{
		mots++;
		i = not_in_quote(s, c, i);
		while (s[i] && s[i] == c)
			i++;
	}
	return (mots);
}

char	*ft_strdup(char *src)
{
	int		i;
	char	*cpy;

	i = 0;
	while (src[i])
		i++;
	cpy = malloc(sizeof(char) * (i + 1));
	if (!(cpy))
		return (NULL);
	i = 0;
	while (src[i])
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	**ft_split_dans_process(char *s, char c)
{
	char	**split;
	int		k;
	int		j;
	int		i;
	int		m;

	k = 0;
	split = NULL;
	m = total_len_dans_process((char *)s, c);
	split = malloc(sizeof(split) * (m + 1));
	if (!(split) || !s)
		return (NULL);
	i = 0;
	while (s[i] && k < m)
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		j = i;
		i = not_in_quote(s, c, i);
		split[k++] = ft_strdup_split_dans_process(s, j, i);
	}
	split[k] = 0;
	return (split);
}
