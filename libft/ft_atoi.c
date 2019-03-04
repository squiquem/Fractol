/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 21:50:39 by squiquem          #+#    #+#             */
/*   Updated: 2017/11/18 21:05:08 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_blank(const char *str)
{
	int k;

	k = 0;
	while (str[k] == ' ' || str[k] == '\t' || str[k] == '\v' ||
			str[k] == '\f' || str[k] == '\r' || str[k] == '\n')
		k++;
	return (k);
}

static int		ft_aff(int p, const char *str)
{
	int i;
	int o;

	o = 0;
	i = p;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			o = o * 10 + str[i] - '0';
		if ((str[i] < '0' || str[i] > '9') && i == p)
			return (0);
		if ((str[i] < '0' || str[i] > '9') && i > p)
			return (o);
		i++;
	}
	return (o);
}

int				ft_atoi(const char *str)
{
	int i;

	i = count_blank(str);
	if (str[i] == '-')
		return (-1 * ft_aff(i + 1, str));
	if (str[i] == '+')
		return (ft_aff(i + 1, str));
	return (ft_aff(i, str));
}
