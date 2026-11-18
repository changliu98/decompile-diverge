void func0(const char *s, int *major, int *minor)
{
	*major = atoi(s);
	*minor = atoi(strchr(s, '.') + 1);
}