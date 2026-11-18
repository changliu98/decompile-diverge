static inline void mtx3x3Transpose(struct axisang *dst, struct axisang *aa)
{
	dst->x = aa->x;
	dst->y = aa->y;
	dst->z = aa->z;
	dst->w = aa->w;

	dst->x = aa->x;
	dst->y = aa->y;
	dst->z = aa->z;
	dst->w = aa->w;

	dst->x = aa->x;
	dst->y = aa->y;
	dst->z = aa->z;
	dst->w = aa->w;
}