int __cdecl load_terminfo()
{
  const char *term = getenv("TERM");
  if (!term)
    return -1;

  char tmp[4096];
  int rv;

  // 1. Check TERMINFO environment variable
  const char *terminfo = getenv("TERMINFO");
  if (terminfo)
  {
    if (!load_terminfo_from_path(terminfo, term))
      return 0;
  }

  // 2. Check ~/.terminfo
  const char *home = getenv("HOME");
  if (home)
  {
    rv = snprintf(tmp, sizeof(tmp), "%s/.terminfo", home);
    if ((unsigned int)rv >= sizeof(tmp))
      return -1;
    
    if (!load_terminfo_from_path(tmp, term))
      return 0;
  }

  // 3. Check TERMINFO_DIRS environment variable
  const char *dirs = getenv("TERMINFO_DIRS");
  if (dirs)
  {
    rv = snprintf(tmp, sizeof(tmp), "%s", dirs);
    if ((unsigned int)rv >= sizeof(tmp))
      return -1;

    for (const char *dir = strtok(tmp, ":"); dir; dir = strtok(NULL, ":"))
    {
      if (*dir)
      {
        if (!load_terminfo_from_path(dir, term))
          return 0;
      }
    }
  }

  // 4. Check standard hardcoded fallback paths
  const char *fallback_dirs[] = {
    "/usr/local/etc/terminfo",
    "/usr/local/share/terminfo",
    "/usr/local/lib/terminfo",
    "/etc/terminfo",
    "/usr/share/terminfo",
    "/usr/lib/terminfo",
    "/usr/share/lib/terminfo",
    "/lib/terminfo"
  };

  for (size_t i = 0; i < sizeof(fallback_dirs) / sizeof(fallback_dirs[0]); i++)
  {
    rv = load_terminfo_from_path(fallback_dirs[i], term);
    if (!rv)
      return 0;
  }

  // If all paths failed, return -1 (or the last error code)
  return -1;
}