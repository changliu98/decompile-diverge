int __cdecl get_tagfname(tagname_T *tnp, int first, char_u *buf)
{
  char *v3; // rax
  char_u **ga_data; // rax
  int tn_hf_idx; // ecx
  char_u *v6; // rax
  size_t v7; // rax
  size_t v8; // rax
  size_t v9; // rax
  char_u *filename; // [rsp+60h] [rbp-40h]
  int i; // [rsp+6Ch] [rbp-34h]
  char_u *r_ptr; // [rsp+70h] [rbp-30h]
  char_u *fname; // [rsp+78h] [rbp-28h]

  if ( first )
    memset(tnp, 0, sizeof(tagname_T));
  if ( *(_DWORD *)curbuf )
  {
    if ( first )
    {
      ga_clear_strings(&tag_fnames);
      ga_init2(&tag_fnames, 8uLL, 10);
      do_in_runtimepath((char_u *)"doc/tags", 1, (void (*)(char_u *, void *))found_tagfile_cb, 0LL);
    }
    if ( tnp->tn_hf_idx < tag_fnames.ga_len )
    {
      ga_data = (char_u **)tag_fnames.ga_data;
      tn_hf_idx = tnp->tn_hf_idx;
      tnp->tn_hf_idx = tn_hf_idx + 1;
      vim_strncpy(buf, ga_data[tn_hf_idx], 0xFFFuLL);
    }
    else
    {
      if ( tnp->tn_hf_idx > tag_fnames.ga_len || !*p_hf )
        return 0;
      ++tnp->tn_hf_idx;
      strcpy((char *)buf, p_hf);
      v3 = (char *)gettail(buf);
      strcpy(v3, (const char *)"tags");
      simplify_filename(buf);
      for ( i = 0; i < tag_fnames.ga_len; ++i )
      {
        if ( !strcmp((const char *)buf, *((const char **)tag_fnames.ga_data + i)) )
          return 0;
      }
    }
    return 1;
  }
  if ( !first )
    goto LABEL_25;
  if ( **(_BYTE **)(curbuf + 8) )
    v6 = vim_strsave(*(char_u **)(curbuf + 8));
  else
    v6 = vim_strsave((char_u *)p_tags);
  tnp->tn_tags = v6;
  if ( !tnp->tn_tags )
    return 0;
  tnp->tn_np = tnp->tn_tags;
  while ( 1 )
  {
LABEL_25:
    while ( !tnp->tn_did_filefind_init )
    {
      if ( !*tnp->tn_np )
      {
        vim_findfile_cleanup(tnp->tn_search_ctx);
        tnp->tn_search_ctx = 0LL;
        return 0;
      }
      *buf = 0;
      copy_option_part(&tnp->tn_np, buf, 4095, " ,");
      r_ptr = vim_findfile_stopdir(buf);
      filename = gettail(buf);
      if ( r_ptr )
      {
        v7 = strlen((const char *)r_ptr);
        memmove(r_ptr + 1, r_ptr, v7 + 1);
        ++r_ptr;
      }
      v8 = strlen((const char *)filename);
      memmove(filename + 1, filename, v8 + 1);
      *filename = 0;
      v9 = strlen((const char *)filename + 1);
      tnp->tn_search_ctx = vim_findfile_init(
                             buf,
                             filename + 1,
                             v9,
                             r_ptr,
                             100,
                             0,
                             0,
                             tnp->tn_search_ctx,
                             1,
                             *(char_u **)(curbuf + 16));
      if ( tnp->tn_search_ctx )
        tnp->tn_did_filefind_init = 1;
    }
    fname = vim_findfile(tnp->tn_search_ctx);
    if ( fname )
      break;
    tnp->tn_did_filefind_init = 0;
  }
  strcpy((char *)buf, (const char *)fname);
  vim_free(fname);
  return 1;
}