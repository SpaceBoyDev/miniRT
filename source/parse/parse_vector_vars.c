/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vector_vars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 21:57:39 by dario             #+#    #+#             */
/*   Updated: 2025/10/24 21:58:37 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

int len_int_vector(char *str)
{
    int i;

    i = -1;
    while (str[++i])
    {
        if (ft_isdigit(str[i]))
            continue ;
		else if ((str[i] == '+') || (str[i] == '-'))
		{
			if (str[i + 1] && ft_isdigit(str[i + 1])
				&& str[i - 1] && !ft_isdigit(str[i - 1]))
				continue ;
			break ;
		}
        else if (str[i] == ',' && i != 0)
        {
            if (str[i + 1] && (ft_isdigit(str[i + 1])
                    || str[i + 1] == '+' || str[i + 1] == '-'))
                continue ;
			break ;
        }
		break ;
    }
    return (i);
}

int len_double_vector(char *str)
{
    int i;

    i = -1;
    while (str[++i])
    {
        if (ft_isdigit(str[i]))
            continue ;
		else if ((str[i] == '+') || (str[i] == '-'))
		{
			if (str[i + 1] && ft_isdigit(str[i + 1])
				&& str[i - 1] && !ft_isdigit(str[i - 1]))
				continue ;
			break ;
		}
        else if ((str[i] == ',' && i != 0) || (str[i] == '.'))
        {
            if (str[i + 1] && (ft_isdigit(str[i + 1])
                    || str[i + 1] == '+' || str[i + 1] == '-'))
                continue ;
			break ;
        }
		break ;
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
	if (!vector)
		return (NULL);
	ft_strlcpy(vector, str, i + 1);	
	table = ft_split(vector, ',');
	if (!table || table_len(table) != 3)
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
	return (str + i);
}

char	*read_double_vector(char *str, double *x, double *y, double *z)
{
	char	**table;
	char	*vector;
	int		i;

	i = len_double_vector(str);

	vector = malloc(sizeof(char) * (i + 1));
	if (!vector)
		return (NULL);
	ft_strlcpy(vector, str, i + 1);	
	table = ft_split(vector, ',');
	if (!table || table_len(table) != 3)
	{
		free(vector);
		free_table(table);
		return (NULL);
	}
	read_double(table[0], x);
	read_double(table[1], y);
	read_double(table[2], z);
	free(vector);
	free_table(table);
	return (str + i);
}
