int load_terminfo() {
 char *term;
 char *path;
 char *home;
 char *dirs;
 char *dir;
 char tmp[4096];
 int rv;

 term = getenv("TERM");
 if (term == NULL)
  return -1;

 path = getenv("TERMINFO");
 if (path != NULL) {
  rv = load_terminfo_from_path(path, term);
  if (rv == 0)
   return 0;
 }

 home = getenv("HOME");
 if (home != NULL) {
  rv = snprintf(tmp, sizeof(tmp), "%s/.terminfo", home);
  if (rv < 0 || rv >= sizeof(tmp))
   return -1;
  rv = load_terminfo_from_path(tmp, term);
  if (rv == 0)
   return 0;
 }

 dirs = getenv("TERMINFO_DIRS");
 if (dirs != NULL) {
  rv = snprintf(tmp, sizeof(tmp), "%s", dirs);
  if (rv < 0 || rv >= sizeof(tmp))
   return -1;
  dir = strtok(tmp, ":");
  while (dir != NULL) {
   if (dir[0] != '\0') {
    rv = load_terminfo_from_path(dir, term);
    if (rv == 0)
     return 0;
   }
   dir = strtok(NULL, ":");
  }
 }

 rv = load_terminfo_from_path("/usr/local/etc/terminfo", term);
 if (rv == 0)
  return 0;
 rv = load_terminfo_from_path("/usr/local/share/terminfo", term);
 if (rv == 0)
  return 0;
 rv = load_terminfo_from_path("/usr/local/lib/terminfo", term);
 if (rv == 0)
  return 0;
 rv = load_terminfo_from_path("/etc/terminfo", term);
 if (rv == 0)
  return 0;
 rv = load_terminfo_from_path("/usr/share/terminfo", term);
 if (rv == 0)
  return 0;
 rv = load_terminfo_from_path("/usr/lib/terminfo", term);
 if (rv == 0)
  return 0;
 rv = load_terminfo_from_path("/usr/share/lib/terminfo", term);
 if (rv == 0)
  return 0;
 rv = load_terminfo_from_path("/lib/terminfo", term);
 if (rv == 0)
  return 0;

 return -1;
}