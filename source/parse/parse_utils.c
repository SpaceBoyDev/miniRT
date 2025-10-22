/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:14:52 by dario             #+#    #+#             */
/*   Updated: 2025/10/22 20:48:29 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

int	table_len(char **table)
{
	int	len;

	len = 0;
	while (table[len])
		++len;
	return (len);
}

bool	is_number(char *str)
{
	int	i;

	i = 0;
	printf("Checkeando char -> %s\n", str);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			printf("posicion %i ", i);
			printf("en char %c", str[i]);
			return (false);
		}
		++i;
	}
	printf("true :3\n");
	return (true);
}

bool	check_trash_line(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\n')
			return (false);
		++str;
	}
	return (true);
}
