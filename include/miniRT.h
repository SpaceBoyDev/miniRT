/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 21:09:15 by dario             #+#    #+#             */
/*   Updated: 2025/12/09 14:29:39 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libs/libft/libft.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "defines.h"
# include "structs.h"

void	print_error(t_error error);
void	exit_error(t_error error, t_scene *scene);
void	free_table(char **table);
void	free_scene(t_scene *scene);

// DEBUG
void	print_data(t_scene *scene);

#endif