static int load_terminfo(void) {
 char *term = getenv("TERM");
 if (!term) return -1;

 char buf[4096];
 int ret;
 int result = -1;


 char *terminfo = getenv("TERMINFO");
 if (terminfo) {
  ret = load_terminfo_from_path(terminfo, term);
  if (!ret) return result = ret;
 }


 char *home = getenv("HOME");
 if (home) {
  while (1) {
   ret = snprintf(buf, sizeof(buf), "%s/.terminfo", home);
   if (ret < 0 || ret >= sizeof(buf)) {
    return result = -1;
   }
   break;
  }

  while (1) {
   ret = load_terminfo_from_path(buf, term);
   if (!ret) return result = ret;
   break;
  }
 }


 char *dirs = getenv("TERMINFO_DIRS");
 if (dirs) {
  while (1) {
   ret = snprintf(buf, sizeof(buf), "%s", dirs);
   if (ret < 0 || ret >= sizeof(buf)) {
    return result = -1;
   }
   break;
  }

  char *dir, *cdir;
  for (dir = strtok(buf, ":"); dir; dir = strtok(NULL, ":")) {
   cdir = dir;
   switch (*cdir) {
   case '\0':
    continue;
   default:
    break;
   }

   ret = load_terminfo_from_path(cdir, term);
   if (!ret) return result = ret;
  }
 }


 ret = load_terminfo_from_path("/usr/local/etc/terminfo", term);
 if (!ret) return result = ret;

 ret = load_terminfo_from_path("/usr/local/share/terminfo", term);
 if (!ret) return result = ret;

 ret = load_terminfo_from_path("/usr/local/lib/terminfo", term);
 if (!ret) return result = ret;

 ret = load_terminfo_from_path("/usr/local/etc/terminfo", term);
 if (!ret) return result = ret;

 ret = load_terminfo_from_path("/usr/share/terminfo", term);
 if (!ret) return result = ret;

 ret = load_terminfo_from_path("/usr/lib/terminfo", term);
 if (!ret) return result = ret;

 ret = load_terminfo_from_path("/usr/share/lib/terminfo", term);
 if (!ret) return result = ret;

 ret = load_terminfo_from_path("/usr/share/lib/terminfo", term);
 if (!ret) return result = ret;

 return result;
}