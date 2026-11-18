static inline void mtxTranspose(struct axisang *dst, struct axisang *aa)
{
	dst->x = aa->x;
	dst->y = aa->y;
	dst->z = aa->z;
	dst->w = aa->w;
	dst->w = aa->w;
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