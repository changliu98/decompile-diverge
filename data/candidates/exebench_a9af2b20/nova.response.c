char *stpCpy(char *s, const char *ct)
{
	while ((*s++ = *ct++)!= '\0')
		s++;
	return s;
}