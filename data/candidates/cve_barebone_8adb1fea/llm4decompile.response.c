void
ga_concat_shorten_esc(garray_T *gap, const char_u *s)
{
    char_u	buf[64 + 1];
    int	    l;
    int	    c;
    int	    c1;
    int	    n;
    char_u	*p;

    if (s == NULL)
    {
	ga_concat(gap, "NULL");
	return;
    }

    while (*s != '\0')
    {
	c = mb_ptr2char_adv(&s);
	p = s;
	l = (int)(s - p);
	n = 1;
	while (*s != '\0' && (c1 = (*mb_ptr2char)(s)) == c)
	{
	    n++;
	    s += l;
	}
	if (n > 20)
	{
	    ga_concat(gap, "\\[");
	    ga_concat_esc(gap, p, l);
	    ga_concat(gap, " occurs ");
	    vim_snprintf((char *)buf, sizeof(buf), "%d", n);
	    ga_concat(gap, buf);
	    ga_concat(gap, " times]");
	    s -= l;
	}
	else
	    ga_concat_esc(gap, p, l);
    }
}