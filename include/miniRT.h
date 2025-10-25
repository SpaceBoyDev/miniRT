/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 21:09:15 by dario             #+#    #+#             */
/*   Updated: 2025/10/25 21:18:37 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libs/libft/libft.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"

// MLX Window
# define WIN_WIDTH	512
# define WIN_HEIGHT	512
# define WIN_NAME	"MiniRT"

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
typedef struct s_vector3	t_vec3;
typedef struct s_vector3	t_coords;

//Typedef ray
typedef struct s_ray		t_ray;

// Typedef data
typedef struct s_data		t_data;

// Typedef scene
typedef struct s_scene		t_scene;

// Typedef Scene Objects
typedef struct s_ambient	t_ambient;
typedef struct s_camera		t_camera;
typedef struct s_light		t_light;

// Typedef Scene Geometry
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
	ERR_DUP_AMB,
	ERR_DUP_CAM,
	ERR_DUP_LIGHT,
	ERR_AMB_RATIO,
	ERR_AMB_COLOR,
	ERR_AMB_TRASH,
	ERR_CAM_COORDS,
	ERR_CAM_ORIENTATION,
	ERR_CAM_FOV,
	ERR_CAM_TRASH,
	ERR_LIGHT_COORDS,
	ERR_LIGHT_RATIO,
	ERR_LIGHT_COLOR,
	ERR_LIGHT_TRASH,
	ERR_SPHERE_COORDS,
	ERR_SPHERE_DIAMETER,
	ERR_SPHERE_COLOR,
	ERR_SPHERE_TRASH,
	ERR_PLANE_COORDS,
	ERR_PLANE_NORMAL,
	ERR_PLANE_COLOR,
	ERR_PLANE_TRASH,
	ERR_CYL_COORDS,
	ERR_CYL_AXIS,
	ERR_CYL_DIAMETER,
	ERR_CYL_HEIGHT,
	ERR_CYL_COLOR,
	ERR_CYL_TRASH,
	ERR_MLX_INIT,
	ERR_MLX_HOOK,
	ERR_MLX_IMG,
	ERR_MLX_IMG_TO_WIN,
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

struct s_ray
{
	t_coords	origin;
	t_vec3		direction;
};

struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		*scene;
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
	t_vec3	orientation;
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
	t_sphere	*next;
};

struct s_plane
{
	t_coords	position;
	t_vec3	normal;
	t_color		color;
	t_plane		*next;
};

struct s_cylinder
{
	t_coords	position;
	t_vec3	axis;
	double		diameter;
	double		height;
	t_color		color;
	t_cylinder	*next;
};

void	print_error(t_error error);
void	exit_error(t_error error, t_scene *scene);
void	free_table(char **table);
void	free_scene(t_scene *scene);

#endif
