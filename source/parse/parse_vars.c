/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:48:25 by dario             #+#    #+#             */
/*   Updated: 2025/10/24 21:58:26 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

double	check_double_sign(char *str, double *result)
{
	if (!str)
		return (0);
	if (str[0] == '-')
		*result *= -1;
	return (*result);
}

bool	s_to_double(char *str, int *i, double *ret)
{
	bool	is_decimal;
	double	decimal;

	is_decimal = false;
	decimal = 1;
	while (str[++*i] && str[*i] != ' ')
	{
		if (str[*i] == '.' && !is_decimal)
			is_decimal = true;
		else if (str[*i] == '.' && is_decimal)
			return (false);
		if ((str[*i] == '+' || str[*i] == '-')
			&& str[*i + 1] && !ft_isdigit(str[*i + 1]))
			return (false);
		if (ft_isdigit(str[*i]) && !is_decimal)
			*ret = (*ret * 10) + (str[*i] - '0');
		else if (ft_isdigit(str[*i]) && is_decimal)
		{
			decimal /= 10;
			*ret += ((str[*i] - '0') * decimal);
		}
	}
	return (true);
}

char	*read_double(char *str, double *result)
{
	int		i;
	double	ret;

	i = -1;
	ret = 0;
	if (!s_to_double(str, &i, &ret))
		return (NULL);
	if (str[i - 1] && !ft_isdigit(str[i - 1]))
		return (NULL);
	*result = check_double_sign(str, &ret);
	return (&str[i]);
}
