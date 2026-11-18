static void func0(const struct vec3 *v1, const struct vec3 *v2,
			   struct vec3 *v3)
{
	v3->x = v1->x * v2->x + v1->y * v2->z + v1->z * v2->y;
	v3->y = v1->x * v2->y + v1->y * v2->x + v1->z * v2->z;
	v3->z = v1->x * v2->z + v1->y * v2->y + v1->z * v2->x;
}