void
vim_strncpy_to_utf8(char_u *src, char_u *dst, int len, int size)
{
    size_t	lenleft;
    size_t	lentot;
    size_t	rest;
    size_t	i;
    size_t	j;
    size_t	k;

    lenleft = len - 3;
    lentot = 0;

    if (*src == NUL)
    {
	if (size > 0)
	    *dst = NUL;
	return;
    }

    if (len < 4)
	lenleft = 0;

    /* Find the number of characters to copy, and the length of that string in
     * bytes. */
    for (i = 0;; ++i)
    {
	if (i >= lenleft && i >= (lentot + 1) / 2)
	    break;

	if (src[i] == NUL)
	{
	    dst[i] = NUL;
	    return;
	}

	rest = ptr2cells(src + i);
	if (lentot + rest > lenleft)
	    break;

	lentot += rest;
	dst[i] = src[i];

	if (has_mbyte)
	{
	    rest = mb_ptr2len(src + i);
	    while (--rest > 0 && ++i != size)
		dst[i] = src[i];
	}
    }

    j = i;

    if (enc_dbcs)
    {
	/* Use vim_strsize() to get the number of screen cells. */
	while ((rest = vim_strsize(src + j)) + lentot > lenleft)
	{
	    rest -= ptr2cells(src + j);
	    j += mb_ptr2len(src + j);
	}
    }
    else if (enc_utf8)
    {
	/* Find the last character that fits. */
	for (k = strlen(src); k > 0; --k)
	{
	    rest = ptr2cells(src + k);
	    if (lentot + rest <= lenleft && k > j)
	    {
		j = k;
		break;
	    }
	}
    }
    else
    {
	/* Assume all characters are one byte. */
	while (j > i && (rest = ptr2cells(src + j)) + lentot > lenleft)
	    --j;
    }

    if (j <= i + 3)
    {
	/* Copy the characters. */
	if (src != dst)
	{
	    lentot = strlen(src);
	    if (lentot >= (size_t)size)
		lentot = (size_t)size - 1;
	    memmove(dst + i, src + i, (lentot - i) + 1);
	}
    }
    else
    {
	/* Copy the first characters and add "...". */
	if (size > i + 3)
	{
	    memcpy__bench(dst + i, src + i, 3);
	    dst[i + 3] = NUL;
	    lentot = strlen(src + j) + 1;
	    if (lentot >= (size_t)size - i - 3)
		lentot = (size_t)size - i - 3 - 1;
	    memmove(dst + i + 3, src + j, lentot);
	    dst[i + 3 + lentot - 1] = NUL;
	}
	else
	    dst[i - 1] = NUL;
    }
}