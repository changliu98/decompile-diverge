static char *stb_skipnewline(char *ptr)
{
	if (*ptr == '\r' || *ptr == '\n') {
		if (*ptr + *(ptr+1) == '\r' + '\n')
			ptr++;
		ptr++;
	}
	return ptr;
}