int get_tagfname(tagname_T *tnp,int first,char_u *buf)

{
  int iVar1;
  char_u *pcVar2;
  size_t sVar3;
  void *pvVar4;
  char_u *local_50;
  char_u *filename;
  int i;
  char_u *r_ptr;
  char_u *fname;
  char_u *buf_local;
  int first_local;
  tagname_T *tnp_local;
  
  if (first != 0) {
    memset(tnp,0,0x20);
  }
  if (curbuf->b_help == 0) {
    if (first != 0) {
      if (*curbuf->b_p_tags == '\0') {
        local_50 = p_tags;
      }
      else {
        local_50 = curbuf->b_p_tags;
      }
      pcVar2 = vim_strsave(local_50);
      tnp->tn_tags = pcVar2;
      if (tnp->tn_tags == (char_u *)0x0) {
        return 0;
      }
      tnp->tn_np = tnp->tn_tags;
    }
    while( true ) {
      while (tnp->tn_did_filefind_init == 0) {
        if (*tnp->tn_np == '\0') {
          vim_findfile_cleanup(tnp->tn_search_ctx);
          tnp->tn_search_ctx = (void *)0x0;
          return 0;
        }
        *buf = '\0';
        copy_option_part(&tnp->tn_np,buf,0xfff," ,");
        r_ptr = vim_findfile_stopdir(buf);
        pcVar2 = gettail(buf);
        if (r_ptr != (char_u *)0x0) {
          sVar3 = strlen((char *)r_ptr);
          memmove(r_ptr + 1,r_ptr,sVar3 + 1);
          r_ptr = r_ptr + 1;
        }
        sVar3 = strlen((char *)pcVar2);
        memmove(pcVar2 + 1,pcVar2,sVar3 + 1);
        *pcVar2 = '\0';
        sVar3 = strlen((char *)(pcVar2 + 1));
        pvVar4 = vim_findfile_init(buf,pcVar2 + 1,sVar3,r_ptr,100,0,0,tnp->tn_search_ctx,1,
                                   curbuf->b_ffname);
        tnp->tn_search_ctx = pvVar4;
        if (tnp->tn_search_ctx != (void *)0x0) {
          tnp->tn_did_filefind_init = 1;
        }
      }
      pcVar2 = vim_findfile(tnp->tn_search_ctx);
      if (pcVar2 != (char_u *)0x0) break;
      tnp->tn_did_filefind_init = 0;
    }
    strcpy((char *)buf,(char *)pcVar2);
    vim_free(pcVar2);
  }
  else {
    if (first != 0) {
      ga_clear_strings(&tag_fnames);
      ga_init2(&tag_fnames,8,10);
      do_in_runtimepath((char_u *)"doc/tags",1,found_tagfile_cb,(void *)0x0);
    }
    pvVar4 = tag_fnames.ga_data;
    if (tnp->tn_hf_idx < tag_fnames.ga_len) {
      iVar1 = tnp->tn_hf_idx;
      tnp->tn_hf_idx = iVar1 + 1;
      vim_strncpy(buf,*(char_u **)((long)pvVar4 + (long)iVar1 * 8),0xfff);
    }
    else {
      if ((tag_fnames.ga_len < tnp->tn_hf_idx) || (*p_hf == '\0')) {
        return 0;
      }
      tnp->tn_hf_idx = tnp->tn_hf_idx + 1;
      strcpy((char *)buf,(char *)p_hf);
      pcVar2 = gettail(buf);
      strcpy((char *)pcVar2,"tags");
      simplify_filename(buf);
      for (i = 0; i < tag_fnames.ga_len; i = i + 1) {
        iVar1 = strcmp((char *)buf,*(char **)((long)tag_fnames.ga_data + (long)i * 8));
        if (iVar1 == 0) {
          return 0;
        }
      }
    }
  }
  return 1;
}