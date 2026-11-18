void rifft1pt(vec2_t v, float scale)
{
	float length, ilength;

	length = v[0]*v[0] + v[1]*v[1];
	if (length > 0)
	{
		ilength = 1.0/sqrt(length);
		v[0] *= scale*ilength;
		v[1] *= scale*ilength;
	} 
}