static void drwav_f32_to_s16(short *out, float *data, size_t len)
{
	size_t i;
	for (i = 0; i < len; i++) {
		float f = data[i];
		union { float f; int16_t s; } u;

		u.f = f;

		if (u.s > +32767.0f)
			u.s = +32767.0f;
		else if (u.s < -32768.0f)
			u.s = -32768.0f;

		u.s += (u.s < 0)? -0.5f : 0.5f;

		out[i] = u.s;
	}
}