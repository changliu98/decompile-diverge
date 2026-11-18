static void Mat4_vec3_mul_T(struct vec3 *dst, const struct vec3 *v1,
		    const struct vec3 *v2)
{
	float x = v1->x * v2->x + v1->y * v2->z + v1->z * v2->y;
	float y = v1->x * v2->y + v1->y * v2->x + v1->z * v2->z;
	float z = v1->x * v2->z + v1->y * v2->y + v1->z * v2->x;

	dst->x = x;
	dst->y = y;
	dst->z = z;
}