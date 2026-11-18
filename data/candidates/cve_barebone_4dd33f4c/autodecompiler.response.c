static int
get_tagfname(
    vim_findfile_T *fd,
    int reset,
    char_u *buf)
{
    char_u *p;
    char_u *fname = NULL;
    int i;
    int retval;

    if (reset)
    {
# ifdef FEAT_MBYTE
#  ifdef FEAT_GUI
        if (gui.in_use && !gui.starting)
            gui_dont_update_cursor();
#  endif
# endif
        memset(fd, 0, sizeof(vim_findfile_T));
    }

    if (curbuf->b_ffname != NULL)
    {
# ifdef FEAT_MBYTE
#  ifdef FEAT_GUI
        if (gui.in_use && !gui.starting)
            gui_dont_update_cursor();
#  endif
# endif

        if (reset)
        {
            ga_clear_strings(&tag_fnames);
            ga_init2(&tag_fnames, (int)sizeof(char_u *), 10);

            do_in_runtimepath((char_u *)"doc/tags", 1, found_tagfile_cb, NULL);
        }

        if (fd->tag_fd >= tag_fnames.ga_len
                || (fd->tag_fd >= tag_fnames.ga_len
                    && p_hf[0] == '\0'))
        {
            int j;

            for (j = 0; j < tag_fnames.ga_len; ++j)
            {
                if (!strcmp(buf, ((char_u **)tag_fnames.ga_data)[j]))
                {
                    retval = 0;
                    goto done;
                }
            }

            vim_strncpy(buf, ((char_u **)tag_fnames.ga_data)[fd->tag_fd++],
                        4096 - 1);
        }
        else
        {
            vim_strncpy(buf, ((char_u **)tag_fnames.ga_data)[fd->tag_fd++],
                        4096 - 1);
        }

        retval = 1;
    }
    else
    {
# ifdef FEAT_MBYTE
#  ifdef FEAT_GUI
        if (gui.in_use && !gui.starting)
            gui_dont_update_cursor();
#  endif
# endif

        if (reset)
        {
            char_u *p;

            if (*curbuf->b_p_tags != NUL)
                p = curbuf->b_p_tags;
            else
                p = p_tags;

            fd->tag_fname = vim_strsave(p);
            if (fd->tag_fname == NULL)
            {
                retval = 0;
                goto done;
            }
            fd->tag_fname_cur = fd->tag_fname;
        }

        while (1)
        {
            if (fd->tag_searching)
            {
                fname = vim_findfile(fd->tag_search_ctx);
                if (fname != NULL)
                    break;

                fd->tag_searching = 0;
            }
            else
            {
                char_u *p;
                char_u *stopdir;
                char_u *tail;
                char_u *newtail;
                char_u *newstopdir;

                p = NULL;
                if (*fd->tag_fname_cur != NUL)
                {
                    buf[0] = NUL;
                    copy_option_part(fd->tag_fname_cur, buf, 4096 - 1, " ,");
                    stopdir = vim_findfile_stopdir(buf);
                    tail = gettail(buf);
                    if (stopdir != NULL)
                    {
                        newstopdir = stopdir + 1;
                        memmove(newstopdir, stopdir, strlen(stopdir) + 1);
                        ++stopdir;
                    }
                    newtail = tail + 1;
                    memmove(newtail, tail, strlen(tail) + 1);
                    *tail++ = NUL;

                    fd->tag_search_ctx = vim_findfile_init(buf, tail,
                            strlen(tail), stopdir, 100, 0, 1, fd->tag_search_ctx);
                    if (fd->tag_search_ctx != NULL)
                        fd->tag_searching = 1;
                }
                else
                {
                    vim_findfile_cleanup(fd->tag_search_ctx);
                    fd->tag_search_ctx = NULL;
                    retval = 0;
                    goto done;
                }
            }
        }
        strcpy(buf, fname);
        vim_free(fname);
        retval = 1;
    }

done:
# ifdef FEAT_MBYTE
#  ifdef FEAT_GUI
    if (gui.in_use && !gui.starting)
        gui_update_cursor();
#  endif
# endif
    return retval;
}