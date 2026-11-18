void
msg_puts_printf(const char_u *str, int maxlen)
{
    const char_u *p = str;
    const char_u *s = str;
    char_u *tofree;

    while (*s != '\0' && (maxlen < 0 || (int)(s - str) < maxlen))
    {
	/* Output one line at a time, unless in silent mode. */
	if ((!silent_mode || *p_verbose) && *s == '\n')
	{
	    char *line;
	    int len = s - p;

	    /* Allocate space for the line and a possible CR. */
	    line = alloc((size_t)(len + 3));
	    if (line != NULL)
	    {
		memcpy(line, p, (size_t)len);
		if (!info_message)
		    line[len++] = '\r';
		line[len++] = '\n';
		line[len] = '\0';
		if (info_message)
		    mch_msg(line);
		else
		    mch_errmsg(line);
		vim_free(line);
	    }
	    p = s + 1;
	}
	if (*s == '\r' || *s == '\n')
	    msg_col = 0;
	else
	    ++msg_col;
	++s;
    }

    /* Output the remaining text, if there is any. */
    if (*p != '\0' && (!silent_mode || *p_verbose))
    {
	tofree = NULL;
	if (maxlen > 0 && (size_t)strlen((char *)p) > (size_t)maxlen)
	{
	    tofree = vim_strnsave(p, (size_t)maxlen);
	    p = tofree;
	}
	if (p != NULL)
	{
	    if (info_message)
		mch_msg(p);
	    else
		mch_errmsg(p);
	    vim_free(tofree);
	}
    }

    msg_didout = 1;
}