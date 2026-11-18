static int get_tagfname(tag_t *tag, int init, char_u *fname) {
  if (init) memset(tag, 0, sizeof(*tag));
  if (tag_opt_ptr->tag_file != 0) {
    if (init) {
      ga_clear_strings(&tag_files);
      ga_init2(&tag_files, sizeof(char_u), 10);
      do_in_runtimepath((char_u *)"doc/tags", 1, get_tagfname_cb, NULL);
    }
    if (tag->tag_file_idx < tag_files.nr) {
      vim_strncpy(fname, (char_u *)tag_files.ptrs[tag->tag_file_idx++],
                  4096 - 1);
    } else if (tag->tag_file_idx <= tag_files.nr &&
               tag_opt_ptr->tag_file_default[0] != '\0') {
      tag->tag_file_idx++;
      strcpy((char *)fname, tag_opt_ptr->tag_file_default);
      strcpy((char *)gettail(fname), "tags");
      simplify_filename(fname);
      for (int i = 0; i < tag_files.nr; ++i) {
        if (strcmp((char *)fname, (char *)tag_files.ptrs[i]) == 0) return 0;
      }
    } else
      return 0;
    return 1;
  }
  if (init) {
    if (tag_opt_ptr->tag_files[0] == '\0')
      tag->tag_files_save = vim_strsave(TAG_FILES_DEFAULT);
    else
      tag->tag_files_save = vim_strsave(tag_opt_ptr->tag_files);
    if (tag->tag_files_save == NULL) return 0;
    tag->tag_files_ptr = tag->tag_files_save;
  }
  while (1) {
    if (!tag->tag_file_valid) {
      if (tag->tag_files_ptr[0] == '\0') {
        vim_findfile_cleanup(tag->tag_file_handle);
        tag->tag_file_handle = NULL;
        return 0;
      }
      fname[0] = '\0';
      copy_option_part(&tag->tag_files_ptr, fname, 4096 - 1, " ,");
      char_u *stopdir = vim_findfile_stopdir(fname);
      char_u *tail = gettail(fname);
      if (stopdir != NULL) {
        memmove(stopdir + 1, stopdir, strlen((char *)stopdir) + 1);
        ++stopdir;
      }
      memmove(tail + 1, tail, strlen((char *)tail) + 1);
      tail[0] = '\0';
      tag->tag_file_handle = vim_findfile_init(
          fname, tail + 1, strlen((char *)tail + 1), stopdir, 100, 0, 0,
          tag->tag_file_handle, 1, tag_opt_ptr->tag_file_case);
      if (tag->tag_file_handle == NULL) continue;
      tag->tag_file_valid = 1;
    }
    char_u *f = vim_findfile(tag->tag_file_handle);
    if (f != NULL) {
      strcpy((char *)fname, (char *)f);
      vim_free(f);
      return 1;
    }
    tag->tag_file_valid = 0;
  }
}