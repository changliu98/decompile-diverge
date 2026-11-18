__attribute__((noinline))
static void
special_keys(char_u *args)
{
    char *save_str = nb_unquote(args, NULL);
    char *tok = strtok(save_str, " ");
    char *sep;
#define KEYBUFLEN 64
    char keybuf[KEYBUFLEN];
    char cmdbuf[256];

    while (tok != NULL)
    {
	int i = 0;

	if ((sep = strchr(tok, '-')) != NULL)
	{
	    *sep = NUL;
	    while (*tok)
	    {
		switch (*tok)
		{
		    case 'A':
		    case 'M':
		    case 'C':
		    case 'S':
			keybuf[i++] = *tok;
			keybuf[i++] = '-';
			break;
		}
		tok++;
	    }
	    tok++;
	}

	if (strlen(tok) + i < KEYBUFLEN)
	{
	    strcpy(&keybuf[i], tok);
	    vim_snprintf(cmdbuf, sizeof(cmdbuf),
				 "<silent><%s> :nbkey %s<CR>", keybuf, keybuf);
	    do_map(MAPTYPE_MAP, (char_u *)cmdbuf, MODE_NORMAL, FALSE);
	}
	tok = strtok(NULL, " ");
    }
    vim_free(save_str);
}