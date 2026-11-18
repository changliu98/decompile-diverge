void int_to_float(void *out, const void *in)
{
	*(float *)out = *(int *)in;
}