/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 05:07:51 by mdouiri           #+#    #+#             */
/*   Updated: 2022/08/11 20:51:54 by mdouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ret_val;

int	not_alphanumeric(char c)
{
	if (!c)
		return (1);
	if (c == 36 || c == 39 || c == 63)
		return (0);
	if (c <= 47 || (c >= 58 && c <= 64) || (c >= 91 && c <= 96) || (c >= 123))
		return (1);
	return (0);
}

int	ft_separateur(char c)
{
	if (c == ' ' || c == '<' || c == '>'
		|| c == '\"' || c == '\'' || c == '=' || not_alphanumeric(c))
		return (1);
	else if (c == '$')
		return (2);
	else if (c == '|')
		return (3);
	else
		return (0);
}

int	chevron(char c)
{
	if (c == '>')
		return (1);
	else if (c == '<')
		return (2);
	return (0);
}

int	pipo(char c)
{
	if (c == ' ')
		return (1);
	else if (c == '|')
		return (2);
	return (0);
}

int	ft_quoti(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	return (0);
}
