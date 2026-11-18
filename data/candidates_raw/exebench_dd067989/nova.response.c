static inline void func0(struct vec3 *dst, const struct vec3 *v1,
			    const struct vec3 *v2)
{
	dst->x = v1->x / v2->x;
	dst->y = v1->y / v2->y;
	dst->z = v1->z / v2->z;
}