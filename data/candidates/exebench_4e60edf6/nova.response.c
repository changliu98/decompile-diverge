static inline void warp_mat4_fill_transpose(struct axisang *dst, struct axisang *aa)
{
	dst->x = aa->x;
	dst->y = aa->y;
	dst->z = aa->z;
	dst->w = aa->w;
	dst->x = aa->x1;
	dst->y = aa->y1;
	dst->z = aa->z1;
	dst->w = aa->w1;
	dst->x = aa->x2;
	dst->y = aa->y2;
	dst->z = aa->z2;
	dst->w = aa->w2;
	dst->x = aa->x3;
	dst->y = aa->y3;
	dst->z = aa->z3;
	dst->w = aa->w3;
}