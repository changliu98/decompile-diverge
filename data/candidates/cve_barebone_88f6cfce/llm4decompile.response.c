void
append_command(const char_u *cmd)
{
    char_u *p;
    char_u *s;
    int l;

    strcat((char *) IObuff, ": ");
    p = IObuff + strlen((char *) IObuff);

    for (s = cmd; *s != '\0' && p - IObuff < 1018; ++s)
    {
	/* Display <Nul> instead of a real NUL character. */
	if (*s == NUL)
	{
	    l = (enc_utf8 && *s == 0xC2 && *(s + 1) == 0xA0) ? 2 : 1;
	    s += l;
	    strcpy((char *) p, "<a0>");
	    p += 4;
	    continue;
	}

	if (has_mbyte)
	    mb_copy_char(&s, &p);
	else
	    *p++ = *s;
    }
    *p = '\0';
}