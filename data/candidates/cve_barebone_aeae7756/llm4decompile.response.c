void
ex_history(exarg_T *eap)
{
    char_u	*arg = eap->arg;
    char_u	*p;
    int	    i;
    int	    idx;
    int	    hisidx1 = 1;
    int	    hisidx2 = -1;
    int	    histype1 = 0;
    int	    histype2 = 0;
    int	    c;
    histentry_T *his;

    if (hislen == 0)
    {
	msg("'history' option is zero");
	return;
    }

    /* Check for a history type. */
    if (*arg != '-' && *arg != ',' && *arg < '0' && *arg > '9')
    {
	p = arg;
	while ((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z')
		|| vim_strchr((char_u *)":=@>/?", *p) != NULL)
	    ++p;
	c = *p;
	*p = '\0';
	histype1 = get_histtype(arg);
	if (histype1 == -1)
	{
	    if (strncasecmp((char *)arg, "all", (int)strlen((char *)arg)) == 0)
		histype1 = 0;
	    else
	    {
		*p = c;
		semsg(e_trailing_characters_str, arg);
		return;
	    }
	}
	histype2 = histype1;
	*p = c;
    }

    /* Check for a range. */
    if (!get_list_range(&arg, &hisidx1, &hisidx2) || *arg != '\0')
    {
	semsg(e_trailing_characters_str, arg);
	return;
    }

    /* Loop over the history types. */
    while (!got_int && histype1 <= histype2)
    {
	strcpy((char *)IObuff, "\n      #  ");
	strcat((char *)IObuff, history_names[histype1]);
	strcat((char *)IObuff, " history");
	msg_puts_title(IObuff);

	idx = hisidx[histype1];
	his = history[histype1];

	/* Translate a negative index into a positive one. */
	if (hisidx1 < 0)
	    hisidx1 = (hislen + hisidx1 + idx + 1) % hislen;
	if (hisidx2 < 0)
	    hisidx2 = (hislen + hisidx2 + idx + 1) % hislen;

	/* Loop over the history entries. */
	if (idx >= 0)
	{
	    i = idx;
	    while (hisidx1 <= hisidx2 && !got_int)
	    {
		if (++i == hislen)
		    i = 0;
		if (his[i].hisstr != NULL && his[i].hisnum >= hisidx1
			&& his[i].hisnum <= hisidx2)
		{
		    msg_putchar('\n');
		    sprintf((char *)IObuff, "%c%6d  ",
			    i == idx ? '>' : ' ', his[i].hisnum);
		    if (vim_strsize(his[i].hisstr) > (int)(Columns - 10))
			trunc_string(his[i].hisstr, (char_u *)IObuff +
				strlen((char *)IObuff), (int)(Columns - 10),
				1024 + 1 - strlen((char *)IObuff));
		    else
			strcat((char *)IObuff, (char *)his[i].hisstr);
		    msg_outtrans(IObuff);
		    out_flush();
		}
		if (i == idx)
		    break;
	    }
	}
	++histype1;
    }
}