static void func0(u32 v, u32 k, u32 *ek, u32 *ekk)
{
	u32 e, ek0, ek1;

	e = v - 0xA5;
	if (k < 0x40)
		e -= 0x41;
	if (k >= 0x80)
		e -= 0x41;
	e -= (e >> 1) & 1;
	e += (e >> 1) & 0xBA;
	ek0 = e % 0xBC;
	ek1 = ek0;
	if (ek0 >= 0x40)
		ek0++;
	ek0 += 0x85;
	*ekk = ek0;
	*ek = ek1;
}