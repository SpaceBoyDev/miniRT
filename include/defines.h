/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 19:45:27 by dario             #+#    #+#             */
/*   Updated: 2025/12/13 19:45:29 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# ifndef DEBUG
#  define DEBUG 0
# endif

// MLX Window
# define WIN_WIDTH	800
# define WIN_HEIGHT	800
# define WIN_NAME	"MiniRT"

// Defines for objects IDs
# define ID_AMBIENT     "A "
# define ID_CAMERA	    "C "
# define ID_LIGHT	    "L "
# define ID_SPHERE	    "sp "
# define ID_PLANE	    "pl "
# define ID_CYL		    "cy "
# define ID_CONE	    "co "
# define ID_PB      	"pb "
# define ID_HB      	"hb "

# define EPS	0.0001f
# define SPEED	1

# ifndef M_PI
#  define M_PI   3.14159265358979323846
# endif

#endif
