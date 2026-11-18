static char pop(const char *str, int *pi)
{
	char ret = -1;
	if (*pi >= 0 && *pi < (int)strlen(str))
		ret = str[(*pi)++];
	return ret;
}