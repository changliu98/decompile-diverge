static void leer_datos_instruccion(unsigned char c1, unsigned char c2,
			     unsigned int *ascii1, unsigned int *ascii2,
			     unsigned int *csum)
{
	*csum = 0;
	if (((c1 >> 2) % 4) == 1)
		*csum = 1;
	*ascii1 = c1 >> 3;
	*ascii2 = ((c1 & 0x3) << 8) + c2;
}