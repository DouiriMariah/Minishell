/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orga_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amattei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 05:22:24 by amattei           #+#    #+#             */
/*   Updated: 2022/08/22 05:22:36 by amattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if ((s1[i] == '\n' || s1[i] == '\0')
			&& (s2[i] == '\n' || s2[i] == '\0'))
			return (0);
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	ft_str(char *env, char *find)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env[i] == find[i])
		i++;
	if (find[i] == '\0')
		return (1);
	return (0);
}

int	ft_found_char(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}

char	*ft_strdupo(char *s, int i)
{
	int		j;
	char	*res;

	res = malloc((i + 1) * sizeof (char));
	if (!res)
		return (0);
	j = 0;
	while (s[j] && j < i)
	{
		res[j] = s[j];
		j++;
	}
	res[j] = '\0';
	return (res);
}

char	*get_next_line(int fd)
{
	char	heap[100];
	char	buff;
	int		nbyte;
	int		i;

	i = 0;
	nbyte = read(fd, &buff, 0x1);
	if (fd < 0)
		return (0);
	while (nbyte > 0x0)
	{
		heap[i++] = buff;
		if (buff == '\n')
			break ;
		nbyte = read(fd, &buff, 0x1);
	}
	heap[i] = '\0';
	if (nbyte <= 0 && i == 0)
		return (0);
	return (ft_strdup(heap));
}
