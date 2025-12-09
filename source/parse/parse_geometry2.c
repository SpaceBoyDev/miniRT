#include "../../include/parse.h"

char	*line_advance_and_init(t_scene *scene, char *line \
, int obj_type, void **obj)
{
	*obj = init_obj(scene, obj_type);
	if (!*obj)
		return (NULL);
	line += 2;
	line = skip_blank(line);
	return (line);
}

static char	*parse_paraboloid_props(char *line, t_paraboloid *pb, int *err)
{
	line = parse_coords(line, &pb->position);
	if (!line)
		return (*err = ERR_PB_COORDS, NULL);
	line = parse_normalized_vector(line, &pb->axis);
	if (!line)
		return (*err = ERR_PB_AXIS, NULL);
	line = parse_double(line, &pb->k_factor);
	if (!line || pb->k_factor <= 0.0)
	{
		*err = ERR_PB_FACTOR;
		return (NULL);
	}
	line = parse_double(line, &pb->h_limit);
	if (!line || pb->h_limit <= 0.0)
		return (*err = ERR_PB_LIMIT, NULL);
	line = parse_color(line, &pb->color);
	if (!line)
		return (*err = ERR_PB_COLOR, NULL);
	return (line);
}

int	parse_paraboloid(char *line, t_scene *scene)
{
	t_paraboloid	*paraboloid;
	char			*ptr;
	int				error_code;

	error_code = OK;
	ptr = line_advance_and_init(scene, line, PARABOLOID, (void **)&paraboloid);
	if (!ptr)
		return (ERR_ALLOC);
	line = parse_paraboloid_props(ptr, paraboloid, &error_code);
	if (!line)
		return (error_code);
	paraboloid->color.r /= 255.0;
	paraboloid->color.g /= 255.0;
	paraboloid->color.b /= 255.0;
	if (!check_trash_line(line))
		return (ERR_PB_TRASH);
	return (OK);
}

static char	*parse_hyperboloid_props(char *line, t_hyperboloid *hb, int *err)
{
	line = parse_coords(line, &hb->position);
	if (!line)
		return (*err = ERR_HB_COORDS, NULL);
	line = parse_normalized_vector(line, &hb->axis);
	if (!line)
		return (*err = ERR_HB_AXIS, NULL);
	line = parse_double(line, &hb->a_param);
	if (!line || hb->a_param <= 0.0)
		return (*err = ERR_HB_APARAM, NULL);
	line = parse_double(line, &hb->b_param);
	if (!line || hb->b_param <= 0.0)
		return (*err = ERR_HB_BPARAM, NULL);
	line = parse_double(line, &hb->c_param);
	if (!line || hb->c_param <= 0.0)
		return (*err = ERR_HB_CPARAM, NULL);
	line = parse_double(line, &hb->h_limit);
	if (!line || hb->h_limit <= 0.0)
		return (*err = ERR_HB_LIMIT, NULL);
	line = parse_color(line, &hb->color);
	if (!line)
		return (*err = ERR_HB_COLOR, NULL);
	return (line);
}

int	parse_hyperboloid(char *line, t_scene *scene)
{
	t_hyperboloid	*hyperboloid;
	char			*ptr;
	int				error_code;

	error_code = OK;
	ptr = line_advance_and_init(scene, line, HYPERBOLOID, \
	(void **)&hyperboloid);
	if (!ptr)
		return (ERR_ALLOC);
	line = parse_hyperboloid_props(ptr, hyperboloid, &error_code);
	if (!line)
		return (error_code);
	hyperboloid->color.r /= 255.0;
	hyperboloid->color.g /= 255.0;
	hyperboloid->color.b /= 255.0;
	if (!check_trash_line(line))
		return (ERR_HB_TRASH);
	return (OK);
}
