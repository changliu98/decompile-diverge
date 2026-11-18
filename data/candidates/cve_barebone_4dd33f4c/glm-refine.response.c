int __cdecl get_tagfname(tagname_T *tnp, int first, char_u *buf)
{
  char_u *r_ptr;
  char_u *filename;
  char_u *fname;
  int i;

  if (first)
    memset(tnp, 0, sizeof(tagname_T));

  // Branch 1: 'curbuf' is non-zero (likely checking a buffer flag or pointer)
  if (*(_DWORD *)curbuf)
  {
    if (first)
    {
      ga_clear_strings(&tag_fnames);
      ga_init2(&tag_fnames, 8uLL, 10);
      do_in_runtimepath((char_u *)"doc/tags", 1, (void (*)(char_u *, void *))found_tagfile_cb, 0LL);
    }

    if (tnp->tn_hf_idx < tag_fnames.ga_len)
    {
      tnp->tn_hf_idx++;
      vim_strncpy(buf, ((char_u **)tag_fnames.ga_data)[tnp->tn_hf_idx - 1], 0xFFFuLL);
    }
    else
    {
      if (tnp->tn_hf_idx > tag_fnames.ga_len || !*p_hf)
        return 0;

      ++tnp->tn_hf_idx;
      strcpy((char *)buf, p_hf);
      strcpy((char *)gettail(buf), "tags");
      simplify_filename(buf);

      for (i = 0; i < tag_fnames.ga_len; ++i)
      {
        if (!strcmp((const char *)buf, ((const char **)tag_fnames.ga_data)[i]))
          return 0;
      }
    }
    return 1;
  }

  // Branch 2: 'curbuf' is zero
  if (first)
  {
    tnp->tn_tags = vim_strsave(**(_BYTE **)(curbuf + 8) ? *(char_u **)(curbuf + 8) : (char_u *)p_tags);
    if (!tnp->tn_tags)
      return 0;

    tnp->tn_np = tnp->tn_tags;
  }

  // Main loop for finding files
  while (1)
  {
    while (!tnp->tn_did_filefind_init)
    {
      if (!*tnp->tn_np)
      {
        vim_findfile_cleanup(tnp->tn_search_ctx);
        tnp->tn_search_ctx = 0LL;
        return 0;
      }

      *buf = 0;
      copy_option_part(&tnp->tn_np, buf, 4095, " ,");
      
      r_ptr = vim_findfile_stopdir(buf);
      filename = gettail(buf);

      if (r_ptr)
      {
        size_t r_len = strlen((const char *)r_ptr);
        memmove(r_ptr + 1, r_ptr, r_len + 1);
        ++r_ptr;
      }

      size_t f_len = strlen((const char *)filename);
      memmove(filename + 1, filename, f_len + 1);
      *filename = 0;

      size_t filename_len = strlen((const char *)filename + 1);
      tnp->tn_search_ctx = vim_findfile_init(
                             buf,
                             filename + 1,
                             filename_len,
                             r_ptr,
                             100,
                             0,
                             0,
                             tnp->tn_search_ctx,
                             1,
                             *(char_u **)(curbuf + 16));

      if (tnp->tn_search_ctx)
        tnp->tn_did_filefind_init = 1;
    }

    fname = vim_findfile(tnp->tn_search_ctx);
    if (fname)
      break;

    tnp->tn_did_filefind_init = 0;
  }

  strcpy((char *)buf, (const char *)fname);
  vim_free(fname);
  return 1;
}