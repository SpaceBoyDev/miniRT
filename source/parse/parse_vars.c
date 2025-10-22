/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:48:25 by dario             #+#    #+#             */
/*   Updated: 2025/10/22 20:32:53 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

char	*read_double(char *str, double *result)
{
	int		i;
	bool	is_decimal;
	double	decimal;
	double	ret;

	i = -1;
	is_decimal = false;
	decimal = 1;
	ret = 0;
	while (str[++i] && str[i] != ' ')
	{
		if (str[i] == '.' && !is_decimal)
			is_decimal = true;
		else if (str[i] == '.' && is_decimal)
			return (NULL);
		if (ft_isdigit(str[i]) && !is_decimal)
			ret += (ret * 10) + (str[i] - '0');
		else if (ft_isdigit(str[i]) && is_decimal)
		{
			decimal /= 10;
			ret += (str[i] - '0') * decimal;
		}
	}
	*result = ret;
	return (&str[i]);
}

char	*read_int_vector(char *str, t_color *result)
{
	char	**table;
	char	*vector;
	int		y;

	y = 0;
	while ((str[y] && ft_isdigit(str[y])) || (str[y] && str[y] == ',' && ft_isdigit(str[y + 1])))
		++y;
	vector = malloc(sizeof(char) * (y + 1));
	ft_strlcpy(vector, str, y + 1);	
	table = ft_split(vector, ',');
	if (!table || table_len(table) != 3 ||
		!is_number(table[0]) || !is_number(table[1])|| !is_number(table[2]))
	{
		free(vector);
		free_table(table);
		return (NULL);
	}
	result->r = ft_atoi(table[0]);
	result->g = ft_atoi(table[1]);
	result->b = ft_atoi(table[2]);
	free(vector);
	free_table(table);
	return (str + y);
}
