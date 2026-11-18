static inline int endGCGdata(const char *input, int *error)
{
	*error = 0;
	return *input == '>' && input[1]!= '\0';
}