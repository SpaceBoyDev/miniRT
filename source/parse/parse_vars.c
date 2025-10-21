/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:48:25 by dario             #+#    #+#             */
/*   Updated: 2025/10/21 17:55:15 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

bool	parse_double(char *str, double *result)
{
	int		i;
	bool	is_decimal;
	double	ret;

	i = 0;
	is_decimal = false;
	ret = 0;
	printf("%s\n", str);
	while (str[i] == ' ')
		++i;
	while (str[i] && str[i] != ' ')
	{
		printf("En el char %c\n", str[i]);
		printf("Decimal: %b\n", is_decimal);
		printf("Double: %f\n", ret);
		if (str[i] == '.' && !is_decimal)
			is_decimal = true;
		else if (str[i] == '.' && is_decimal)
			return (false);
		if (ft_isdigit(str[i]) && !is_decimal)
			ret += (ret * 10) + (str[i] - '0');
		else if (ft_isdigit(str[i]) && is_decimal)
		{
			printf("que\n");
			ret += (str[i] - '0');
			ret /= 10;
		}
		printf("\n");
		++i;
	}
	printf("Terminao bien %f\n", ret);

	*result = ret;
	return (true);
}
