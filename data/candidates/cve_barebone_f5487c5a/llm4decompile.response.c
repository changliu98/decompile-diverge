void
ReplaceXmpValue(StringInfo profile, size_t start, size_t end, const char *value)
{
	size_t		oldlen = GetStringInfoLength(profile);
	size_t		newlen;
	size_t		valuelen = strlen(value);
	char	   *olddata;

	newlen = oldlen - (end - start) + valuelen;
	if (newlen > oldlen)
		SetStringInfoLength(profile, newlen);

	olddata = GetStringInfoDatum(profile);
	memmove(olddata + start + valuelen, olddata + end, oldlen - end);
	memcpy(olddata + start, value, valuelen);

	if (newlen < oldlen)
	{
		SetStringInfoLength(profile, newlen);
		olddata[newlen] = '\0';
	}
}