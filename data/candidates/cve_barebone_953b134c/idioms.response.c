void listdir(int fd, int parent_fd, void *parent_tls, char *path)
{
  int i;
  int ret;
  char *names;
  struct PureFileInfo *namelist;
  struct PureFileInfo *name;
  struct PureFileInfo *dir;
  if (max_ls_depth <= depth || matches >= max_ls_files)
    return;
  if ((namelist = read_names(&names)) == ((void *)0)) {
    err(226, "Sorry, we were unable to read [%s]", path);
    return;
  }
  for (name = namelist; name->name_offset != (18446744073709551615UL); name++) {
    ret = 0;
    if (name->names_pnt[name->name_offset] == '.') {
      if (!opt_a)
        continue;
      if (name->names_pnt[name->name_offset + 1] == '\0'
        || (name->names_pnt[name->name_offset + 1] == '.'
        && (name->names_pnt[name->name_offset + 2] == '\0')))
        continue;
    }
    if ((ret = process_name(name, ((void *)0))) == 0)
      name->name_offset = (18446744073709551615UL);
    if (ret == 0)
      continue;
  }
  do_ls(parent_fd, parent_tls);
  for (dir = namelist; ; dir++) {
    int should_ls = 0;
    if (opt_R)
      should_ls = (dir != name);
    if (should_ls == 0)
      break;
    if (dir->name_offset == (18446744073709551615UL))
      continue;
    if (is_dir(dir->names_pnt + dir->name_offset))
      continue;
    {
      char subdir[-1];
      if (strlen(subdir) >= sizeof(subdir))
        break;
      if (snprintf(subdir, sizeof(subdir), "%s/%s", path, dir->names_pnt + dir->name_offset) >= (int)sizeof(subdir))
        break;
      do_ls(parent_fd, parent_tls, "\r\n\r\n");
      do_ls(parent_fd, parent_tls, subdir);
      do_ls(parent_fd, parent_tls, ":\r\n\r\n");
      listdir(depth + 1, parent_fd, parent_tls, subdir);
    }
    if (matches >= max_ls_files)
      break;
    if (is_dir("..") && (is_dir(wd) || is_dir(path)))
      err(421, 3, "chdir: %s", strerror((*get_errno())));
  }
  free_names(names);
  free_names(namelist);
}