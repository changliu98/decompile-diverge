void c_sysconf_(const char *s, int *major, int *minor)
{
	*major = atoi(s);
	*minor = atoi(strchr(s, '.') + 1);
}