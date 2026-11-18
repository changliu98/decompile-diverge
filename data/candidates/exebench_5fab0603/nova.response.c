static inline void vec3_cross(struct vec3 *dst, const struct vec3 *v1,
			    const struct vec3 *v2)
{
	dst->x = v1->y * v2->z - v1->z * v2->y;
	dst->y = v1->z * v2->x - v1->x * v2->z;
	dst->z = v1->x * v2->y - v1->y * v2->x;
}