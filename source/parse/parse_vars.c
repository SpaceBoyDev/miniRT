/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:48:25 by dario             #+#    #+#             */
/*   Updated: 2025/10/22 23:16:53 by dario            ###   ########.fr       */
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

int len_int_vector(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (ft_isdigit(str[i]))
            ++i;
        else if (str[i] == ',' || str[i] == '+' || str[i] == '-')
        {
            if (str[i + 1] && (ft_isdigit(str[i + 1])
                    || str[i + 1] == '+' || str[i + 1] == '-'))
            {
                ++i;
                continue;
            }
            break;
        }
		else
			break;
    }
    return (i);
}

int len_double_vector(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (ft_isdigit(str[i]))
        {
            ++i;
            continue;
        }
		if (str[i] == '+' || str[i] == '-')
		{
			if (!str[i + 1] || !ft_isdigit(str[i + 1]))
			{
				++i;
				break;
			}
		}
        if (str[i] == ',')
        {
            if (str[i + 1] && (ft_isdigit(str[i + 1])
                    || str[i + 1] == '+' || str[i + 1] == '-'))
            {
                ++i;
                continue;
            }
            break;
        }
        break;
    }
    return (i);
}

char	*read_int_vector(char *str, t_color *result)
{
	char	**table;
	char	*vector;
	int		i;

	i = len_int_vector(str);

	vector = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(vector, str, i + 1);	
	printf("Vector = %s\n", vector);
	table = ft_split(vector, ',');
	if (!table || table_len(table) != 3)
	{
		free(vector);
		free_table(table);
		return (NULL);
	}
	// int x = 0;
	// while (table[x])
	// {
	// 	printf("->%s", table[x]);
	// 	++x;
	// }
	result->r = ft_atoi(table[0]);
	result->g = ft_atoi(table[1]);
	result->b = ft_atoi(table[2]);
	free(vector);
	free_table(table);
	return (str + i);
}

char	*read_double_vector(char *str, t_color *result)
{
	char	**table;
	char	*vector;
	int		i;

	i = len_int_vector(str);

	vector = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(vector, str, i + 1);	
	printf("Vector = %s\n", vector);
	table = ft_split(vector, ',');
	if (!table || table_len(table) != 3)
	{
		free(vector);
		free_table(table);
		return (NULL);
	}
	// int x = 0;
	// while (table[x])
	// {
	// 	printf("->%s", table[x]);
	// 	++x;
	// }
	result->r = ft_atoi(table[0]);
	result->g = ft_atoi(table[1]);
	result->b = ft_atoi(table[2]);
	free(vector);
	free_table(table);
	return (str + i);
}
