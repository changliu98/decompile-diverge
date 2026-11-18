int
bracketed_paste(int mode, int drop_count, struct garray_T *gap)
{
    int		c;
    char_u	buf[64];
    int		i = 0;
    char_u	*p;
    int		old_no_mapping;
    int		old_allow_keys;
    int		old_p_paste;
    int		started_syntax = FALSE;
#ifdef FEAT_GUI
    int		gui_stopped = FALSE;
#endif
    int		timeout = -1;

    p = find_termcode("PASTE");
    if (p != NULL && strlen((char *)p) > 64 + 1)
	p = NULL;	/* PASTE too long */

    ++no_mapping;
    old_allow_keys = allow_keys;
    allow_keys = 0;
    old_p_paste = p_paste;
    if (!p_paste)
	set_option_value((char_u *)"paste", 0L, (char_u *)NULL, 0);
#ifdef FEAT_GUI
    gui_stopped = gui.in_use;
    if (gui.in_use)
	gui.dying = TRUE;
#endif

    /*
     * Loop until a non-escaped key was pressed.
     */
    for (;;)
    {
	/*
	 * Show the cursor after a few seconds, if we are still waiting for a
	 * character and no characters arrived yet.
	 */
	if (i == 0 && mode != 1 && mode != 2
#ifdef FEAT_GUI
		&& !gui_stopped
#endif
		)
	    show_cursor(FALSE);

	/*
	 * Wait for a character.
	 */
	c = vgetc();
	show_cursor(TRUE);

	/*
	 * Check for ESC.
	 */
	if (c == 0x1b || c == 0x1001 || c == 0x1002)
	{
	    /* Show the cursor again. */
	    show_cursor(FALSE);
	    if (c == 0x1001 || c == 0x1002)
	    {
		/* Show the cursor again. */
		show_cursor(FALSE);
		/* Repeat the last command. */
		redo_command++;
	    }
	    break;
	}

	/*
	 * Check for timeout.
	 */
	if (c == 0x1003)
	{
	    if (timeout < 0)
	    {
		/* Show the cursor again. */
		show_cursor(FALSE);
		/* Repeat the last command. */
		redo_command++;
	    }
	    break;
	}

	/*
	 * Check for interrupt.
	 */
	if (c == 0 || got_int
#ifdef FEAT_EXCRYPT
		|| enc_dying
#endif
		|| (ex_normal_busy > 0 && c == 3))
	{
	    /* Show the cursor again. */
	    show_cursor(FALSE);
	    break;
	}

	/*
	 * Check for a multi-byte character.
	 */
	if (has_mbyte)
	    i += (*mb_char2bytes)(c, buf + i);
	else
	    buf[i++] = c;
	buf[i] = NUL;

	/*
	 * Check for match with the PASTE termcap entry.
	 */
	if (p != NULL && strncmp((char *)buf, (char *)p, i) != 0)
	{
	    /* No match, add the character to the cmdline. */
	    if (mode == 1)
		put_on_cmdline(buf, i, TRUE);
	    else if (gap != NULL && ga_grow(gap, i) == 1)
	    {
		memmove(((char *)gap->ga_data) + gap->ga_len,
			buf, (size_t)i);
		gap->ga_len += i;
	    }
	    i = 0;
	}
	else
	{
	    /* Match found, don't add the character to the cmdline. */
	    if (p != NULL && p[i] == NUL)
	    {
		/* Full match. */
		break;
	    }
	}
    }

    --no_mapping;
    allow_keys = old_allow_keys;
    if (!old_p_paste)
	set_option_value((char_u *)"paste", 0L, (char_u *)NULL, 0);

#ifdef FEAT_GUI
    if (gui.dying)
	gui.in_use = FALSE;
#endif

    return timeout;
}