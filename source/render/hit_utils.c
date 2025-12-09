#include "../../include/render.h"
#include "../../include/vector.h"

void	update_best(t_hit *best, t_hit *candidate)
{
	if (candidate->did_hit && (!best->did_hit
			|| candidate->distance < best->distance))
		*best = *candidate;
}
