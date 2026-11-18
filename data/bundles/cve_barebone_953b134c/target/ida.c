void __cdecl listdir(unsigned int depth, int f, void *const tls_fd, const char *name)
{
  int *v4; // rax
  char *v5; // rax
  _BYTE v6[15]; // [rsp+0h] [rbp-60h] BYREF
  bool v7; // [rsp+Fh] [rbp-51h]
  size_t sizeof_subdir; // [rsp+10h] [rbp-50h]
  char *alloca_subdir; // [rsp+18h] [rbp-48h]
  int d; // [rsp+24h] [rbp-3Ch]
  PureFileInfo *r; // [rsp+28h] [rbp-38h]
  PureFileInfo *s; // [rsp+30h] [rbp-30h]
  char *names; // [rsp+38h] [rbp-28h] BYREF
  PureFileInfo *dir; // [rsp+40h] [rbp-20h]
  const char *namea; // [rsp+48h] [rbp-18h]
  void *tls_fda; // [rsp+50h] [rbp-10h]
  int fa; // [rsp+58h] [rbp-8h]
  unsigned int deptha; // [rsp+5Ch] [rbp-4h]

  deptha = depth;
  fa = f;
  tls_fda = tls_fd;
  namea = name;
  if ( depth >= max_ls_depth || matches >= (unsigned int)max_ls_files )
    return;
  dir = sreaddir(&names);
  if ( !dir )
  {
    addreply(226, "Sorry, we were unable to read [%s]", namea);
    return;
  }
  for ( s = dir; s->name_offset != -1LL; ++s )
  {
    d = 0;
    if ( (*s->names_pnt)[s->name_offset] != 46 )
      goto LABEL_14;
    if ( !opt_a )
      goto LABEL_15;
    if ( (*s->names_pnt)[s->name_offset + 1]
      && ((*s->names_pnt)[s->name_offset + 1] != 46 || (*s->names_pnt)[s->name_offset + 2]) )
    {
LABEL_14:
      d = listfile(s, 0LL);
    }
    else
    {
      listfile(s, 0LL);
    }
LABEL_15:
    if ( !d )
      s->name_offset = -1LL;
  }
  outputfiles(fa, tls_fda);
  for ( r = dir; ; ++r )
  {
    v7 = 0;
    if ( opt_R )
      v7 = r != s;
    if ( !v7 )
      break;
    if ( r->name_offset != -1LL && !chdir(&(*r->names_pnt)[r->name_offset]) )
    {
      sizeof_subdir = 4097LL;
      alloca_subdir = &v6[-4112];
      if ( v6 == (_BYTE *)&loc_100F + 1 )
        break;
      if ( snprintf(alloca_subdir, 0x1001uLL, "%s/%s", namea, &(*r->names_pnt)[r->name_offset]) < 4097 )
      {
        wrstr(fa, tls_fda, "\r\n\r\n");
        wrstr(fa, tls_fda, alloca_subdir);
        wrstr(fa, tls_fda, ":\r\n\r\n");
        listdir(deptha + 1, fa, tls_fda, alloca_subdir);
      }
      if ( matches >= (unsigned int)max_ls_files )
        break;
      if ( chdir("..") && (chdir(wd) || chdir(namea)) )
      {
        v4 = __errno_location();
        v5 = strerror(*v4);
        die(421, 3, "chdir: %s", v5);
      }
    }
  }
  free(names);
  free(dir);
}