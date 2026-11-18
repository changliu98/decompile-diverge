void mtxMultiply(vec3_t va, vec3_t vb, vec3_t out)
{
	out[0] = vb[1]*va[2] - vb[2]*va[1];
	out[1] = vb[2]*va[0] - vb[0]*va[2];
	out[2] = vb[0]*va[1] - vb[1]*va[0];
}