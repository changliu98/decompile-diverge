int get_tagfname(struct tagname_t *tnp, int first, char *name)
{
  char *line;
  char *tag;
  char *file;
  int i;
  if (first)
    tagname_init(tnp, 0, sizeof(tagname_t));
  if (curbuf->b_rfd == 0) {
    if (first) {
      if (curbuf->b_fname[0])
        tnp->tn_tags = tagname_gettags(curbuf->b_fname);
      else
        tnp->tn_tags = tagname_gettags(p_tags);
      if (tnp->tn_tags == ((void *)0))
        return 0;
      tnp->tn_np = tnp->tn_tags;
      for (;;) {
        if (tnp->tn_np[0] == '\0') {
          tagname_free_search_ctx(tnp->tn_search_ctx);
          tnp->tn_search_ctx = ((void *)0);
          return 0;
        }
        *name = '\0';
        tagname_getnext(&tnp->tn_np, name, 4096 - 1, " ,");
        line = tagname_getline(name);
        file = tagname_getfile(name);
        if (line != ((void *)0)) {
          strlcpy(line + 1, line, tagname_strlen(line + 1) + 1);
          line++;
        }
        strlcpy(file + 1, file, tagname_strlen(file + 1) + 1);
        file[0] = '\0';
        tnp->tn_search_ctx = tagname_search(name, file + 1,
                                             tagname_strlen(file + 1),
                                             line, 100,
                                             ((void *)0), ((void *)0),
                                             tnp->tn_search_ctx,
                                             1,
                                             curbuf->b_mode);
        if (tnp->tn_search_ctx != ((void *)0))
          tnp->tn_did_filefind_init = 1;
      }
    }
    file = tagname_getfile(tnp->tn_search_ctx);
    if (file == ((void *)0)) {
      tnp->tn_did_filefind_init = 0;
      goto next;
    }
    strlcpy(name, file, sizeof(name));
    tagname_free_file(file);
    return 1;
  next:
    if (curbuf->b_rfd == 0)
      return 0;
    if (first) {
      tagname_init_tagfile(&tag_fnames);
      tagname_set_tagfile(&tag_fnames, sizeof(tagname_tagfile), 10);
      tagname_add_tagfile("doc/tags", 1,
                          tagname_found_tagfile_cb, ((void *)0));
    }
    if (tnp->tn_hf_idx >= tag_fnames.ga_len) {
      if (tnp->tn_hf_idx > tag_fnames.ga_len || p_hf == ((void *)0))
        return 0;
      tnp->tn_hf_idx++;
      get_tagfname(name, p_hf);
      strlcat(name, "/", sizeof(name));
      strlcat(name, "tags", sizeof(name));
      tagname_stripname(name);
      for (i = 0; i < tag_fnames.ga_len; i++) {
        if (tagname_is_tagfile(name, (char *)tag_fnames.ga_data[i]))
          return 1;
      }
      return 0;
    }
    get_tagfname(name, (char *)tag_fnames.ga_data[tnp->tn_hf_idx++],
                    sizeof(name) - 1);
    return 1;
  }
  if (first) {
    if (curbuf->b_fname[0])
      tnp->tn_tags = tagname_gettags(curbuf->b_fname);
    else
      tnp->tn_tags = tagname_gettags(p_tags);
    if (tnp->tn_tags == ((void *)0))
      return 0;
    tnp->tn_np = tnp->tn_tags;
    for (;;) {
      if (tnp->tn_np[0] == '\0') {
        tagname_free_search_ctx(tnp->tn_search_ctx);
        tnp->tn_search_ctx = ((void *)0);
        return 0;
      }
      *name = '\0';
      tagname_getnext(&tnp->tn_np, name, 4096 - 1, " ,");
      line = tagname_getline(name);
      file = tagname_getfile(name);
      if (line != ((void *)0)) {
        strlcpy(line + 1, line, tagname_strlen(line + 1) + 1);
        line++;
      }
      strlcpy(file + 1, file, tagname_strlen(file + 1) + 1);
      file[0] = '\0';
      tnp->tn_search_ctx = tagname_search(name, file + 1,
                                          tagname_strlen(file + 1),
                                          line, 100,
                                          ((void *)0), ((void *)0),
                                          tnp->tn_search_ctx,
                                          1,
                                          curbuf->b_mode);
      if (tnp->tn_search_ctx != ((void *)0))
        tnp->tn_did_filefind_init = 1;
    }
  }
  file = tagname_getfile(tnp->tn_search_ctx);
  if (file == ((void *)0)) {
    tnp->tn_did_filefind_init = 0;
    goto next;
  }
  strlcpy(name, file, sizeof(name));
  tagname_free_file(file);
  return 1;
}