void func0(const struct quat *q1, const struct quat *q2, struct quat *out)
{
	out->x = q1->x * q2->x - q1->y * q2->y - q1->z * q2->z - q1->w * q2->w;
	out->y = q1->x * q2->y + q1->y * q2->x - q1->z * q2->w + q1->w * q2->z;
	out->z = q1->x * q2->z + q1->y * q2->w + q1->z * q2->x - q1->w * q2->y;
	out->w = q1->x * q2->w - q1->y * q2->z + q1->z * q2->y + q1->w * q2->x;
}