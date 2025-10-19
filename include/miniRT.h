/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 21:09:15 by dario             #+#    #+#             */
/*   Updated: 2025/10/20 00:27:37 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libs/libft/libft.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"

# define WIDTH		512
# define HEIGHT		512

# define ID_AMBIENT	"A"
# define ID_CAMERA	"C"
# define ID_LIGHT	"L"
# define ID_SPHERE	"sp"
# define ID_PLANE	"pl"
# define ID_CYL		"cy"

typedef enum e_error		t_error;

typedef struct s_color		t_color;
typedef struct s_vector3	t_vector3;
typedef struct s_scene		t_scene;
typedef struct s_ambient	t_ambient;

enum e_error
{
	OK = 0,
	ERR_ALLOC,
	ERR_ARGS,
	ERR_EXTENSION,
	ERR_OPEN,
	ERR_OBJ_ID,
	MAX_ERR_CODE,
};

struct s_color
{
	int	r;
	int	g;
	int	b;
};

struct s_vector3
{
	double	x;
	double	y;
	double	z;
};

struct s_scene
{

};

struct s_ambient
{
	double		lighting;
	t_color		color;
};

// error_handling.c
void	exit_error(t_error error);

#endif