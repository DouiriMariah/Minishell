/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amattei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:37:44 by amattei           #+#    #+#             */
/*   Updated: 2022/08/17 17:37:45 by amattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ret_val;

static int	ft_counto(long int nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		count++;
	while (nb > 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

static int	ft_strlenio(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

static char	*strrev(char *str)
{
	int		i;
	int		len;
	char	tmp;

	i = 0;
	len = ft_strlenio(str) - 1;
	while (i < len)
	{
		tmp = str[i];
		str[i] = str[len];
		str[len] = tmp;
		i++;
		len--;
	}
	return (str);
}

static void	ft_continuo(char *res, long int nb, int sign)
{
	int	v;

	v = 0;
	if (nb == 0)
	{
		res[v] = 0 + 48;
		v++;
	}
	while (nb != 0)
	{
		res[v++] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (sign == 1)
		res[v++] = '-';
	res[v] = '\0';
}

char	*ft_itoa(int n)
{
	char			*res;
	int				sign;
	long int		nb;

	nb = n;
	sign = 0;
	if (nb < 0)
	{
		nb = -nb;
		sign++;
	}
	res = malloc((ft_counto(nb) + sign + 1) * sizeof(char));
	if (!res)
		return (0);
	ft_continuo(res, nb, sign);
	strrev(res);
	return (res);
}
