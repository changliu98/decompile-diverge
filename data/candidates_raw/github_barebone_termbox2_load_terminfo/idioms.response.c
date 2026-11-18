int terminfo_get()
{
  char *termname; char *path; char *path2; char *path3;
  char buf[4096];
  int ret;
  termname = getenv("TERM");
  if (termname == ((void *)0))
    return -1;
  if ((path = getenv("TERMINFO")) != ((void *)0)) {
    ret = terminfo_get_file(path, termname);
    if (ret == 0)
      return 0;
  }
  if ((path = getenv("HOME")) != ((void *)0)) {
    ret = snprintf(buf, sizeof buf, "%s/.terminfo", path);
    if (ret >= (int)sizeof buf)
      return -1;
    ret = terminfo_get_file(buf, termname);
    if (ret == 0)
      return 0;
  }
  if ((path = getenv("TERMINFO_DIRS")) != ((void *)0)) {
    ret = snprintf(buf, sizeof buf, "%s", path);
    if (ret >= (int)sizeof buf)
      return -1;
    for (path2 = strsep(&buf, ":"); path2 != ((void *)0); path2 = strsep(((void *)0), ":")) {
      if (*path2 == '\0')
        continue;
      ret = terminfo_get_file(path2, termname);
      if (ret == 0)
        return 0;
    }
  }
  ret = terminfo_get_file("/usr/local/etc/terminfo", termname);
  if (ret == 0)
    return 0;
  ret = terminfo_get_file("/usr/local/share/terminfo", termname);
  if (ret == 0)
    return 0;
  ret = terminfo_get_file("/usr/local/lib/terminfo", termname);
  if (ret == 0)
    return 0;
  ret = terminfo_get_file("/etc/terminfo", termname);
  if (ret == 0)
    return 0;
  ret = terminfo_get_file("/usr/share/terminfo", termname);
  if (ret == 0)
    return 0;
  ret = terminfo_get_file("/usr/lib/terminfo", termname);
  if (ret == 0)
    return 0;
  ret = terminfo_get_file("/usr/share/lib/terminfo", termname);
  if (ret == 0)
    return 0;
  ret = terminfo_get_file("/lib/terminfo", termname);
  if (ret == 0)
    return 0;
  return -1;
}