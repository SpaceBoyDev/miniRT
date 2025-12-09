#ifndef STRUCTS_H
# define STRUCTS_H

// Typedef ENUM error
typedef enum e_error		t_error;

// Typedef special atributes
typedef struct s_color		t_color;
typedef struct s_vector3	t_vec3;
typedef struct s_vector3	t_coords;

//Typedef ray
typedef struct s_ray		t_ray;
typedef struct s_hit		t_hit;

// Typedef data
typedef struct s_data		t_data;

// Typedef scene
typedef struct s_scene		t_scene;

// Typedef fps
typedef struct s_fps		t_fps;

// Typedef ENUM Geometry ID
typedef enum e_geometry_id	t_id;

// Typedef Scene Objects
typedef struct s_ambient	t_ambient;
typedef struct s_camera		t_camera;
typedef struct s_light		t_light;

// Union geo
typedef union u_geo			t_geo;

// Typedef Object
typedef struct s_obj		t_obj;

// Typedef Scene Geometry
typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;
typedef struct s_cone		t_cone;

// Typedef aux structs
typedef struct s_ray_params	t_ray_params;
typedef struct s_ray_quad	t_ray_quad;
typedef struct s_quad		t_quad;
typedef struct s_pb_ctx		t_pb_ctx;
typedef struct s_cyl_data	t_cyl_data;
typedef struct s_perp		t_perp;

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
	ERR_CONE_COORDS,
	ERR_CONE_AXIS,
	ERR_CONE_DIAMETER,
	ERR_CONE_HEIGHT,
	ERR_CONE_COLOR,
	ERR_CONE_TRASH,
	ERR_HB_COORDS,
	ERR_HB_AXIS,
	ERR_HB_APARAM,
	ERR_HB_BPARAM,
	ERR_HB_CPARAM,
	ERR_HB_LIMIT,
	ERR_HB_COLOR,
	ERR_HB_TRASH,
	ERR_PB_AXIS,
	ERR_PB_COORDS,
	ERR_PB_FACTOR,
	ERR_PB_LIMIT,
	ERR_PB_COLOR,
	ERR_PB_TRASH,
	MAX_ERR_CODE,
	ERR_MLX_INIT,
	ERR_MLX_HOOK,
	ERR_MLX_IMG,
	ERR_MLX_IMG_TO_WIN,
};

struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		*scene;
	t_fps		*fps;
};

struct s_fps
{
	double	frame_times[60];
	int		index;
	int		count;
	double	last_update;
	double	current_fps;
};

struct s_color
{
	double	r;
	double	g;
	double	b;
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

struct s_hit
{
	bool	did_hit;
	double	distance;
	t_vec3	hit_point;
	t_vec3	normal;
	t_color	color;
	t_obj	*hit_obj;
};

struct s_scene
{
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;
	t_obj		*objs;
};

struct s_ambient
{
	double		lighting;
	t_color		color;
};

struct s_camera
{
	t_coords	position;
	t_vec3		orientation;
	int			fov;
};

struct s_light
{
	t_coords	position;
	double		brightness;
	t_color		color;
};

enum e_geometry_id
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
	PARABOLOID,
	HYPERBOLOID,
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
	t_vec3		normal;
	t_color		color;
};

struct s_cylinder
{
	t_coords	position;
	t_vec3		axis;
	double		diameter;
	double		height;
	t_color		color;
};

struct s_cone
{
	t_coords	position;
	t_vec3		axis;
	double		diameter;
	double		height;
	t_color		color;
};

typedef struct s_paraboloid
{
	t_coords	position;
	t_coords	axis;
	double		k_factor;
	double		h_limit;
	t_color		color;
}	t_paraboloid;

typedef struct s_hyperboloid
{
	t_coords	position;
	t_vec3		axis;
	double		a_param;
	double		b_param;
	double		c_param;
	double		h_limit;
	t_color		color;
}	t_hyperboloid;

union u_geo
{
	t_sphere		sphere;
	t_plane			plane;
	t_cylinder		cylinder;
	t_cone			cone;
	t_paraboloid	paraboloid;
	t_hyperboloid	hyperboloid;
};

struct s_obj
{
	t_id	id;
	t_geo	*geo;
	t_obj	*next;
};

struct s_ray_params
{
	t_vec3	forward;
	t_vec3	up;
	t_vec3	right;
	double	px;
	double	py;
};

struct s_ray_quad
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
};

struct s_pb_ctx
{
	t_paraboloid	*pb;
	t_vec3			axis;
	t_obj			*obj;
	t_ray			*r;
};

struct s_cyl_data
{
	t_cylinder	*cyl;
	t_vec3		axis;
	double		radius;
	t_obj		*obj;
};

struct s_quad
{
	double	a;
	double	b;
	double	c;
	double	disc;
};

struct s_perp
{
	t_vec3	d_perp;
	t_vec3	oc_perp;
};

#endif