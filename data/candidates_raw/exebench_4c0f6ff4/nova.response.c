static inline int func0(const char *input, int *error)
{
	*error = 0;
	return *input == '>' && input[1]!= '\0';
}