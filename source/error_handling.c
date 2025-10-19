/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:51:46 by dario             #+#    #+#             */
/*   Updated: 2025/10/20 00:27:09 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

static const char	*g_message[MAX_ERR_CODE] = {
	"",
	"Could not allocate memory",
	"There must be only one argument.\nHow to execute: './miniRT <file.rt>'",
	"The scene file must have the .rt extension",
	"Could not open file",
	"Wrong scene object identifier",
};

void	print_error(t_error error)
{
	if (error == OK)
		return ;
	printf(RED "Error: %s" RST "\n", g_message[error]);
}

void	exit_error(t_error error)
{
	if (error == OK)
		return ;
	print_error(error);
	exit (error);
}