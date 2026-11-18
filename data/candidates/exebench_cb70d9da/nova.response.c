void BTIC2D_TransDCT_Vert( vec3_t in, vec3_t out ){
	int i;
	vec3_t temp;
	vec_t d;

	for ( i = 0; i < 3; i++ )
	{
		temp[i] = in[i];
	}

	d = temp[0] + temp[1];
	temp[2] = temp[2] + temp[0] - temp[1];
	temp[1] = temp[1] + temp[1] - temp[0] + temp[2];
	temp[0] = temp[0] + d;

	d = temp[0] + temp[1];
	temp[2] = temp[2] + temp[0] - temp[1];
	temp[1] = temp[1] + temp[1] - temp[0] + temp[2];
	temp[0] = temp[0] + d;

	d = temp[0] + temp[1];
	temp[2] = temp[2] + temp[0] - temp[1];
	temp[1] = temp[1] + temp[1] - temp[0] + temp[2];
	temp[0] = temp[0] + d;

	d = temp[0] + temp[1];
	temp[2] = temp[2] + temp[0] - temp[1];
	temp[1] = temp[1] + temp[1] - temp[0] + temp[2];
	temp[0] = temp[0] + d;

	d = temp[0] + temp[1];
	temp[2] = temp[2] + temp[0] - temp[1];
	temp[1] = temp[1] + temp[1] - temp[0] + temp[2];
	temp[0] = temp[0] + d;

	d = temp[0] + temp[1];
	temp[2] = temp[2] + temp[0] - temp[1];
	temp[1] = temp[1] + temp[1] - temp[0] + temp[2];
	temp[0] =