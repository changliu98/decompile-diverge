static char func0(const char *str, int *pi)
{
	char ret = -1;
	if (*pi >= 0 && *pi < (int)strlen(str))
		ret = str[(*pi)++];
	return ret;
}