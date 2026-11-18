static void IndexToData(u8 *reg, u8 *h, u8 *l)
{
	*l = reg & 0x03;
	*h = reg >> 2;
}