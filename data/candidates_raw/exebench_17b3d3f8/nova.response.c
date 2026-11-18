static void func0(char *dest, int c)
{
	dest[0] = hex_asc[c >> 4];
	dest[1] = hex_asc[c & 0xf];
}