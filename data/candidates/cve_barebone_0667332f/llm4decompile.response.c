int
bracketed_paste(paste_mode_T mode, int drop, garray_T *gap)
{
    char_u	buf[80 + 1];
    int		idx = 0;
    int		c;
    int		save_paste = p_paste;
    int		save_allow_keys = allow_keys;
    int		one_char = -1;
    char_u	*end;

    end = find_termcode("PE");
    if (end != NULL && strlen((char *)end) > 64)
	end = NULL;

    ++no_mapping;
    allow_keys = 0;

    if (!p_paste)
	set_option_value((char_u *)"paste", 1L, NULL, 0);

    while (end != NULL || (c = vpeekc()) != 0)
    {
	do
	{
	    c = vgetc();
	}
	while (c == 0x1001 || c == 0x1002 || c == 0x1003);

	if (c == 0 || got_int || ex_normal_busy > 0 && c == '\003')
	    break;

	if (has_mbyte)
	    idx += (*mb_char2bytes)(c, buf + idx);
	else
	    buf[idx++] = c;
	buf[idx] = '\0';

	if (end != NULL && !strncmp((char *)buf, (char *)end, idx))
	{
	    if (end[idx] == '\0')
		break;
	    continue;
	}

	if (!drop)
	{
	    switch (mode)
	    {
		case PASTE_INSERT:
		    if (stop_arrow() == 1)
		    {
			if (idx == 1 && (buf[0] == '\r' || buf[0] == NUL
				|| buf[0] == '\n'))
			    ins_eol(buf[0]);
			else
			{
			    ins_char_bytes(buf, idx);
			    AppendToRedobuffLit(buf, idx);
			}
		    }
		    break;
		case PASTE_CMDLINE:
		    put_on_cmdline(buf, idx, 1);
		    break;
		case PASTE_EX:
		    if (gap != NULL && ga_grow(gap, idx) == 1)
		    {
			memmove(gap->ga_data + gap->ga_len, buf, idx);
			gap->ga_len += idx;
		    }
		    break;
		case PASTE_ONE_CHAR:
		    if (one_char == -1)
		    {
			if (has_mbyte)
			    one_char = (*mb_ptr2char)(buf);
			else
			    one_char = buf[0];
		    }
		    break;
	    }
	}
	idx = 0;
    }

    --no_mapping;
    allow_keys = save_allow_keys;

    if (!save_paste)
	set_option_value((char_u *)"paste", 0L, NULL, 0);

    return one_char;
}