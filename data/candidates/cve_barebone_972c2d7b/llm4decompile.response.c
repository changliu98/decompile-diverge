char_u *
regtilde(char_u *source, int magic)
{
    char_u *s;
    char_u *d;
    char_u *newsub;
    char_u *p;
    int l;

    newsub = source;
    for (s = source; *s != '\0'; s++)
    {
	if (*s == '~' && magic)
	{
	    if (reg_prev_sub != NULL)
	    {
		l = (int)strlen((char *)reg_prev_sub);
		p = alloc((size_t)strlen((char *)newsub) + l);
		if (p != NULL)
		{
		    d = p;
		    memmove(p, newsub, (size_t)(s - newsub));
		    p += s - newsub;
		    memmove(p, reg_prev_sub, (size_t)l);
		    p += l;
		    if (magic)
			++s;
		    strcpy((char *)p, (char *)(s + 1));
		    if (newsub != source)
			vim_free(newsub);
		    newsub = d;
		    s = p - 1;
		}
	    }
	    else
	    {
		if (magic)
		    memmove(s, s + 1, (size_t)strlen((char *)(s + 1)) + 1);
		else
		    memmove(s, s + 2, (size_t)strlen((char *)(s + 2)) + 1);
		--s;
	    }
	}
	else if (*s == '\\' && s[1] == '~' && !magic)
	{
	    if (reg_prev_sub != NULL)
	    {
		l = (int)strlen((char *)reg_prev_sub);
		p = alloc((size_t)strlen((char *)newsub) + l);
		if (p != NULL)
		{
		    d = p;
		    memmove(p, newsub, (size_t)(s - newsub));
		    p += s - newsub;
		    memmove(p, reg_prev_sub, (size_t)l);
		    p += l;
		    if (magic)
			++s;
		    strcpy((char *)p, (char *)(s + 1));
		    if (newsub != source)
			vim_free(newsub);
		    newsub = d;
		    s = p - 1;
		}
	    }
	    else
	    {
		if (magic)
		    memmove(s, s + 1, (size_t)strlen((char *)(s + 1)) + 1);
		else
		    memmove(s, s + 2, (size_t)strlen((char *)(s + 2)) + 1);
		--s;
	    }
	}
	else
	{
	    if (*s == '\\' && s[1] != '\0')
		++s;
	    if (has_mbyte)
		s += (*mb_ptr2len)(s) - 1;
	}
    }

    vim_free(reg_prev_sub);
    reg_prev_sub = vim_strsave(newsub);

    return newsub;
}