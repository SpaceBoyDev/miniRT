#include "../../include/render.h"
#include "../../include/vector.h"

static t_vec3	get_world_up(t_vec3 forward)
{
	if (fabs(forward.y) > 0.999)
		return ((t_vec3){0, 0, 1});
	return ((t_vec3){0, 1, 0});
}

static t_ray_params	calculate_camera_basis(t_camera *cam, int x, int y)
{
	t_ray_params	p;
	double			aspect_ratio;
	double			fov_adjust;
	t_vec3			world_up;

	aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	fov_adjust = tan((cam->fov * M_PI / 180.0) / 2.0);
	p.px = (2 * ((x + 0.5) / (double)WIN_WIDTH) - 1)
		* aspect_ratio * fov_adjust;
	p.py = (1 - 2 * ((y + 0.5) / (double)WIN_HEIGHT)) * fov_adjust;
	p.forward = vec3_normalize(cam->orientation);
	world_up = get_world_up(p.forward);
	p.right = vec3_normalize(vec3_cross(p.forward, world_up));
	p.up = vec3_cross(p.right, p.forward);
	return (p);
}

static t_vec3	calculate_direction(t_ray_params *p)
{
	t_vec3	cam_dir;
	t_vec3	dir_x;
	t_vec3	dir_y;
	t_vec3	dir;

	cam_dir = (t_vec3){p->px, p->py, 1.0};
	dir_x = vec3_scale(p->right, cam_dir.x);
	dir_y = vec3_scale(p->up, cam_dir.y);
	dir = vec3_add(dir_x, dir_y);
	dir = vec3_add(dir, vec3_scale(p->forward, cam_dir.z));
	return (vec3_normalize(dir));
}

t_ray	generate_ray(t_camera *cam, int x, int y)
{
	t_ray_params	params;
	t_vec3			dir;
	t_ray			ray;

	params = calculate_camera_basis(cam, x, y);
	dir = calculate_direction(&params);
	ray.origin = cam->position;
	ray.direction = dir;
	return (ray);
}
