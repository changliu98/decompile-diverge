int __cdecl load_terminfo()
{
  const char *dir; // [rsp+8h] [rbp-1038h]
  char *dirs; // [rsp+10h] [rbp-1030h]
  char *home; // [rsp+18h] [rbp-1028h]
  char *terminfo; // [rsp+20h] [rbp-1020h]
  char *term; // [rsp+28h] [rbp-1018h]
  char tmp[4096]; // [rsp+30h] [rbp-1010h] BYREF
  int rv; // [rsp+1038h] [rbp-8h]

  term = getenv("TERM");
  if ( !term )
    return -1;
  terminfo = getenv("TERMINFO");
  if ( terminfo )
  {
    rv = load_terminfo_from_path(terminfo, term);
    if ( !rv )
      return 0;
  }
  home = getenv("HOME");
  if ( home )
  {
    rv = snprintf(tmp, 0x1000uLL, "%s/.terminfo", home);
    if ( (unsigned int)rv >= 0x1000 )
      return -1;
    rv = load_terminfo_from_path(tmp, term);
    if ( !rv )
      return 0;
  }
  dirs = getenv("TERMINFO_DIRS");
  if ( dirs )
  {
    rv = snprintf(tmp, 0x1000uLL, "%s", dirs);
    if ( (unsigned int)rv >= 0x1000 )
      return -1;
    for ( dir = strtok(tmp, ":"); dir; dir = strtok(0LL, ":") )
    {
      if ( *dir )
      {
        rv = load_terminfo_from_path(dir, term);
        if ( !rv )
          return 0;
      }
    }
  }
  rv = load_terminfo_from_path("/usr/local/etc/terminfo", term);
  if ( !rv )
    return 0;
  rv = load_terminfo_from_path("/usr/local/share/terminfo", term);
  if ( !rv )
    return 0;
  rv = load_terminfo_from_path("/usr/local/lib/terminfo", term);
  if ( !rv )
    return 0;
  rv = load_terminfo_from_path("/etc/terminfo", term);
  if ( !rv )
    return 0;
  rv = load_terminfo_from_path("/usr/share/terminfo", term);
  if ( !rv )
    return 0;
  rv = load_terminfo_from_path("/usr/lib/terminfo", term);
  if ( !rv )
    return 0;
  rv = load_terminfo_from_path("/usr/share/lib/terminfo", term);
  if ( !rv )
    return 0;
  rv = load_terminfo_from_path("/lib/terminfo", term);
  if ( rv )
    return -1;
  else
    return 0;
}