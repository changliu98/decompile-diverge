void
trunc_string(const char_u *str, char_u *buf, int room, int buflen)
{
    size_t l;
    int	    i, j, n;
    size_t  half;

    /* compute the length of the string in cells */
    l = 0;
    room -= 3;		/* for "..." */
    if (room < 0)
	room = 0;

    if (*str == '\0')
    {
	if (buflen > 0)
	    *buf = '\0';
	return;
    }

    /* copy the string until it's full */
    for (i = 0; l < room / 2 && i < buflen; ++i)
    {
	if (str[i] == '\0')
	{
	    buf[i] = '\0';
	    return;
	}
	n = ptr2cells(str + i);
	if (l + n > room / 2)
	    break;
	l += n;
	buf[i] = str[i];
	if (has_mbyte)
	{
	    n = (*mb_ptr2len)(str + i);
	    while (--n > 0)
		if (++i >= buflen)
		    break;
	}
    }

    /*
     * If the string is full, we need to make it shorter.
     * 1. If DBCS is off, we just use the length of the string.
     * 2. If DBCS is on, we need to find a place where the string can be
     *    broken.
     */
    if (enc_dbcs)
    {
	n = vim_strsize(str + i);
	while (l + n > room)
	{
	    n -= ptr2cells(str + i);
	    i += (*mb_ptr2len)(str + i);
	}
    }
    else if (enc_utf8)
    {
	/* find a place where the string can be broken */
	for (j = strlen(str); ; )
	{
	    half = j - utf_head_off(str, str + j - 1);
	    if (half == 0 || !utf_iscomposing(utf_ptr2char(str + half)))
	    {
		n = ptr2cells(str + half);
		if (l + n <= room && half > 0)
		{
		    l += n;
		    j = half;
		}
		else
		    break;
	    }
	    --j;
	}
    }
    else
    {
	/* find a place where the string can be broken */
	for (j = strlen(str); ; --j)
	    if (j - 1 >= 0)
	    {
		n = ptr2cells(str + j - 1);
		if (l + n <= room)
		{
		    l += n;
		}
		else
		    break;
	    }
	    else
		break;
    }

    /*
     * If the string is still too long, we put "..." in the middle.
     * If there is room for at least one extra character, put the last part
     * of the string after the "...".
     */
    if (i + 3 >= j)
    {
	if (str != buf)
	{
	    l = strlen(str);
	    if (l >= buflen)
		l = buflen - 1;
	    n = l - i + 1;
	    if (n > 0)
		memmove(buf + i, str + i, n);
	    else
		buf[i - 1] = '\0';
	}
	return;
    }

    if (i + 3 < buflen)
    {
	buf[i++] = '.';
	buf[i++] = '.';
	buf[i++] = '.';
	l = strlen(str + j) + 1;
	if (l >= buflen - i)
	    l = buflen - i - 1;
	memmove(buf + i, str + j, l);
	buf[i + l - 1] = '\0';
    }
    else
	buf[i - 1] = '\0';
}