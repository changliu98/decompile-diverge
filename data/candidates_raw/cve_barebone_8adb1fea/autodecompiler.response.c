void
ga_concat_str(garray_T *gap, char_u *str)
{
    int		c;
    int		len;
    int		same_len;
    char_u	*p;
    char_u	*start;
    char_u	buf[100];

    if (str == NULL)
    {
	ga_concat(gap, "NULL");
	return;
    }

    start = str;
    while (*str != NUL)
    {
	/* Count the number of same characters. */
	same_len = 1;
	p = str;
	c = mb_ptr2char_adv(&p);
	len = p - str;
	while (*p != NUL && mb_ptr2char(p) == c)
	{
	    ++same_len;
	    p += len;
	}

	if (same_len > 20)
	{
	    /* Use \\[...] to denote the repeated characters. */
	    ga_concat(gap, "\\[");
	    ga_concat_esc(gap, start, len);
	    ga_concat(gap, " occurs ");
	    vim_snprintf((char *)buf, sizeof(buf), "%d", same_len);
	    ga_concat(gap, buf);
	    ga_concat(gap, " times]");
	    --p;	/* compensate for the extra p++ in the loop */
	}
	else
	    ga_concat_esc(gap, start, len);

	start = p;
    }
}