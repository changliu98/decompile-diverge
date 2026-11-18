void load_scl_mat(float* t, float tx, float ty, float tz)
{
	t[0] = 1.0f; t[1] = 0.0f; t[2] = 0.0f; t[3] = 0.0f;
	t[4] = 0.0f; t[5] = 1.0f; t[6] = 0.0f; t[7] = 0.0f;
	t[8] = 0.0f; t[9] = 0.0f; t[10] = 1.0f; t[11] = 0.0f;
	t[12] = tx; t[13] = ty; t[14] = tz; t[15] = 1.0f;
}