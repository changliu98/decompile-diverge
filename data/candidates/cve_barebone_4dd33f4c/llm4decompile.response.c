int
get_tagfname(tagname_T *tnp, int first, char_u *buf)
{
    char_u	*p;
    char_u	*stopdir;
    char_u	*tags;

    if (first)
	memset(tnp, 0, sizeof(tagname_T));

    if (curbuf->b_help)
    {
	char_u **fnames;

	if (first)
	{
	    ga_clear_strings(&tag_fnames);
	    ga_init2(&tag_fnames, 8, 10);
	    do_in_runtimepath((char_u *)"doc/tags", 1, found_tagfile_cb, NULL);
	}
	fnames = tag_fnames.ga_data;

	if (tnp->tn_hf_idx < tag_fnames.ga_len)
	{
	    vim_strncpy(buf, fnames[tnp->tn_hf_idx++], (1024 -1));
	    return 1;
	}
	else if (tnp->tn_hf_idx <= tag_fnames.ga_len && *p_hf != '\0')
	{
	    int i;

	    ++tnp->tn_hf_idx;
	    strcpy((char *)buf, (char *)p_hf);
	    p = gettail(buf);
	    strcpy((char *)p, "tags");
	    simplify_filename(buf);
	    for (i = 0; i < tag_fnames.ga_len; ++i)
		if (!strcmp((char *)buf, (char *)fnames[i]))
		    return 0;
	    return 1;
	}
	return 0;
    }

    if (first)
    {
	/* Use the file name from the 'tags' option. */
	if (*curbuf->b_p_tags != '\0')
	    tags = curbuf->b_p_tags;
	else
	    tags = p_tags;
	tnp->tn_tags = vim_strsave(tags);
	if (tnp->tn_tags == NULL)
	    return 0;
	tnp->tn_np = tnp->tn_tags;
    }

    for (;;)
    {
	if (!tnp->tn_did_filefind_init)
	{
	    if (*tnp->tn_np == '\0')
		break;
	    *buf = '\0';
	    copy_option_part(&tnp->tn_np, buf, (1024 -1), " ,");
	    stopdir = vim_findfile_stopdir(buf);
	    p = gettail(buf);
	    if (stopdir != NULL)
	    {
		memmove(stopdir + 1, stopdir, strlen((char *)stopdir) + 1);
		stopdir++;
	    }
	    memmove(p + 1, p, strlen((char *)p) + 1);
	    *p = '\0';
	    tnp->tn_search_ctx = vim_findfile_init(buf, p + 1,
						   (int)strlen((char *)(p + 1)),
						   stopdir, 100,
						   0,
						   NULL,
						   tnp->tn_search_ctx,
						   1,
						   curbuf->b_ffname);
	    if (tnp->tn_search_ctx != NULL)
		tnp->tn_did_filefind_init = 1;
	}
	else
	{
	    p = vim_findfile(tnp->tn_search_ctx);
	    if (p != NULL)
	    {
		strcpy((char *)buf, (char *)p);
		vim_free(p);
		return 1;
	    }
	    tnp->tn_did_filefind_init = 0;
	}
    }

    vim_findfile_cleanup(tnp->tn_search_ctx);
    tnp->tn_search_ctx = NULL;

    return 0;
}