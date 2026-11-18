static void matrixApply(const struct vec5_t *v, float x, float y, float *u,
			   float *v1)
{
	*u = v->x * x + v->y * y + v->z;
	*v1 = v->w * x + v->x * y + v->t;
}