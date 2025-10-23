/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 21:09:15 by dario             #+#    #+#             */
/*   Updated: 2025/10/23 19:33:52 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libs/libft/libft.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"

# define WIDTH		512
# define HEIGHT		512

// Defines for objects IDs
# define ID_AMBIENT	"A "
# define ID_CAMERA	"C "
# define ID_LIGHT	"L "
# define ID_SPHERE	"sp "
# define ID_PLANE	"pl "
# define ID_CYL		"cy "

// Typedef ENUM error
typedef enum e_error		t_error;

// Typedef special atributes
typedef struct s_color		t_color;
typedef struct s_vector3	t_vector3;
typedef struct s_vector3	t_coords;

// Typedef scene
typedef struct s_scene		t_scene;

// Typedef Scene Objects
typedef struct s_ambient	t_ambient;
typedef struct s_camera		t_camera;
typedef struct s_light		t_light;

// Typedef Geometry
typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;

enum e_error
{
	OK = 0,
	ERR_ALLOC,
	ERR_ARGS,
	ERR_EXTENSION,
	ERR_OPEN,
	ERR_OBJ_ID,
	ERR_TRASH_LINE,
	ERR_DUP_AMB,
	ERR_DUP_CAM,
	ERR_DUP_LIGHT,
	ERR_BAD_RATIO,
	ERR_BAD_COLOR,
	ERR_BAD_COORDS,
	ERR_BAD_ORIENTATION,
	ERR_BAD_FOV,
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
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;
	t_sphere	*sphere_list;
	t_plane		*plane_list;
	t_cylinder	*cylinder_list;
};

struct s_ambient
{
	double		lighting;
	t_color		color;
};

struct s_camera
{
	t_coords	position;
	t_vector3	orientation;
	int			fov;
};

struct s_light
{
	t_coords	position;
	double		brightness;
	t_color		color;
};

struct s_sphere
{
	t_coords	position;
	double		diameter;
	t_color		color;
};

struct s_plane
{
	t_coords	position;
	t_vector3	axis;
	t_color		color;
};

struct s_cylinder
{
	t_coords	position;
	t_vector3	axis;
	double		diameter;
	double		height;
	t_color		color;
};


void	exit_error(t_error error, t_scene *scene);
void	free_table(char **table);
void	free_scene(t_scene *scene);

#endif
