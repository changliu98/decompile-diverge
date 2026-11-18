void
ex_history(
    exarg_T *eap )
{
    int		type = 0;
    int		type2 = 0;
    int		idx = 1;
    int		idx2 = -1;
    char_u	*p;
    int		i;
    int		j;
    int		k;
    int		l;
    int		hist_start, hist_end;
    int		c;
    char_u	*s;

    p = eap->arg;
    if (hislen == 0)
    {
	msg((char_u *)"'history' option is zero");
	return;
    }

    /* Check for a type specifier. */
    if ((isdigit(*p) || *p == '-' || *p == ',') && !get_list_range(&p, &idx, &idx2))
    {
	semsg((char_u *)"E488: Trailing characters: %s", p);
	return;
    }
    else
    {
	if (p[0] != NUL)
	{
	    char_u	*cp;

	    /* Find start of non-type part. */
	    cp = p;
	    while ((c = *cp) == 'A' || c == 'a' || c == '0' || c == ':' ||
		    c == '@' || c == '>' || c == '?')
		++cp;
	    c = *cp;
	    *cp = NUL;
	    type = get_histtype(p);
	    if (type == -1)
	    {
		/* Use the type name. */
		cp = p;
		if (strncasecmp((char *)cp, "all", (size_t)strlen(p)) == 0)
		{
		    type = 0;
		    type2 = 4;
		}
		else
		{
		    *cp = c;
		    semsg((char_u *)"E488: Trailing characters: %s", p);
		    return;
		}
	    }
	    else
		type2 = type;
	    *cp = c;
	}
    }

    /* Get the range. */
    if (get_list_range(&p, &idx, &idx2) || *p != NUL)
    {
	semsg((char_u *)"E488: Trailing characters: %s", p);
	return;
    }

    /* Now we know what to print. */
    for (i = type; i <= type2; ++i)
    {
	if (got_int)
	    break;
	if (i > type)
	{
	    msg_putchar('\n');
	    msg_putchar('\n');
	}
	strcpy(IObuff, "\n      #  ");
	strcat(IObuff, (char *)history_names[i]);
	strcat(IObuff, " history");
	msg_puts_title(IObuff);

	/* Start at the oldest entry. */
	j = hisidx[i];
	hist_start = idx;
	hist_end = idx2;
	if (hist_start < 0)
	{
	    if (hist_start - idx < hislen)
		hist_start = 0;
	    else
		hist_start = (j + (hislen - hist_start) + 1) % hislen;
	}
	if (hist_end < 0)
	{
	    if (hist_end - idx < hislen)
		hist_end = 0;
	    else
		hist_end = (j + (hislen - hist_end) + 1) % hislen;
	}

	for (l = j; l >= 0 && l <= hist_end; --l)
	{
	    if (got_int)
		break;
	    if (l == j)
		l = hislen;
	    if (history[i][l].seq != 0 && history[i][l].seq >= hist_start
						      && history[i][l].seq <= hist_end)
	    {
		msg_putchar('\n');
		sprintf(IObuff, "%c%6d  ", l == j ? '>' : ' ', history[i][l].seq);
		if (vim_strsize(history[i][l].seq) > Columns - 10)
		{
		    s = history[i][l].seq;
		    p = IObuff + strlen(IObuff);
		    k = (int)Columns - 10;
		    trunc_string(s, p, k, 1024L - (p - IObuff));
		}
		else
		    strcat(IObuff, history[i][l].seq);
		msg_outtrans(IObuff);
		out_flush();
	    }
	}
    }
}