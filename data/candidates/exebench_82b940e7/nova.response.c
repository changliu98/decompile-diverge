static void clamp(u32 *a, u32 *b, u32 base)
{
	u32 rem;

	*b += *a / base;
	rem = *a % base;
	*a = rem;
}