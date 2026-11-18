int load_terminfo(void) {
  char *term;
  char *terminfo;
  char *home;
  char *dirs;
  char buf[4096];
  int ret;
  term = getenv("TERM");
  if (!term) return -1;
  terminfo = getenv("TERMINFO");
  if (terminfo) {
    ret = load_terminfo_from_path(terminfo, term);
    if (!ret) return 0;
  }
  home = getenv("HOME");
  if (home) {
    ret = snprintf(buf, sizeof(buf), "%s/.terminfo", home);
    if (ret < 0 || ret >= sizeof(buf)) return -1;
    ret = load_terminfo_from_path(buf, term);
    if (!ret) return 0;
  }
  dirs = getenv("TERMINFO_DIRS");
  if (dirs) {
    char *dir;
    ret = snprintf(buf, sizeof(buf), "%s", dirs);
    if (ret < 0 || ret >= sizeof(buf)) return -1;
    dir = strtok(buf, ":");
    while (dir) {
      if (dir[0]) {
        ret = load_terminfo_from_path(dir, term);
        if (!ret) return 0;
      }
      dir = strtok(NULL, ":");
    }
  }
  ret = load_terminfo_from_path("/usr/local/etc/terminfo", term);
  if (!ret) return 0;
  ret = load_terminfo_from_path("/usr/local/share/terminfo", term);
  if (!ret) return 0;
  ret = load_terminfo_from_path("/usr/local/lib/terminfo", term);
  if (!ret) return 0;
  ret = load_terminfo_from_path("/etc/terminfo", term);
  if (!ret) return 0;
  ret = load_terminfo_from_path("/usr/share/terminfo", term);
  if (!ret) return 0;
  ret = load_terminfo_from_path("/usr/lib/terminfo", term);
  if (!ret) return 0;
  ret = load_terminfo_from_path("/usr/share/lib/terminfo", term);
  if (!ret) return 0;
  ret = load_terminfo_from_path("/lib/terminfo", term);
  if (!ret) return 0;
  return -1;
}