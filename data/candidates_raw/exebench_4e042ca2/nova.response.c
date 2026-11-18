void func0( const float scale[3], float shear[12] ){
	int i;

	for ( i = 0; i < 3; i++ )
	{
		shear[i] = 0.0f;
		shear[i + 3] = -scale[i];
		shear[i + 6] = 0.0f;
		shear[i + 9] = 0.0f;
		shear[i + 12] = 0.0f;
	}
}