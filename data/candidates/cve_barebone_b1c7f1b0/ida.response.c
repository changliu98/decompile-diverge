int __cdecl do_core_note(
        magic_set *ms,
        unsigned __int8 *nbuf,
        uint32_t type,
        int swap,
        uint32_t namesz,
        uint32_t descsz,
        size_t noff,
        size_t doff,
        int *flags,
        size_t size,
        int clazz)
{
  uint32_t v12; // [rsp+0h] [rbp-3E0h]
  uint32_t v13; // [rsp+8h] [rbp-3D8h]
  uint32_t v14; // [rsp+10h] [rbp-3D0h]
  uint32_t v15; // [rsp+18h] [rbp-3C8h]
  bool v16; // [rsp+26h] [rbp-3BAh]
  bool v17; // [rsp+27h] [rbp-3B9h]
  __int64 v18; // [rsp+28h] [rbp-3B8h]
  bool v19; // [rsp+47h] [rbp-399h]
  __int64 v20; // [rsp+48h] [rbp-398h]
  __int64 v21; // [rsp+60h] [rbp-380h]
  unsigned __int64 v22; // [rsp+70h] [rbp-370h]
  unsigned __int64 v23; // [rsp+80h] [rbp-360h]
  size_t v24; // [rsp+88h] [rbp-358h]
  magic_set *v25; // [rsp+90h] [rbp-350h]
  char *v26; // [rsp+98h] [rbp-348h]
  uint32_t v27; // [rsp+A0h] [rbp-340h]
  uint32_t v28; // [rsp+A4h] [rbp-33Ch]
  uint32_t v29; // [rsp+A8h] [rbp-338h]
  int adjust; // [rsp+B4h] [rbp-32Ch]
  size_t no; // [rsp+B8h] [rbp-328h]
  size_t k; // [rsp+C0h] [rbp-320h]
  size_t noffset; // [rsp+C8h] [rbp-318h]
  size_t reloffset; // [rsp+D0h] [rbp-310h]
  unsigned __int8 *cp; // [rsp+D8h] [rbp-308h]
  unsigned __int8 *cname; // [rsp+E0h] [rbp-300h]
  unsigned __int8 c; // [rsp+EFh] [rbp-2F1h]
  size_t j; // [rsp+F0h] [rbp-2F0h]
  size_t i; // [rsp+F8h] [rbp-2E8h]
  NetBSD_elfcore_procinfo pi; // [rsp+100h] [rbp-2E0h] BYREF
  char sbuf[512]; // [rsp+1A0h] [rbp-240h] BYREF
  int os_style; // [rsp+3ACh] [rbp-34h]
  uint32_t descsza; // [rsp+3B0h] [rbp-30h]
  uint32_t namesza; // [rsp+3B4h] [rbp-2Ch]
  int swapa; // [rsp+3B8h] [rbp-28h]
  uint32_t typea; // [rsp+3BCh] [rbp-24h]
  unsigned __int8 *nbufa; // [rsp+3C0h] [rbp-20h]
  magic_set *msa; // [rsp+3C8h] [rbp-18h]

  msa = ms;
  nbufa = nbuf;
  typea = type;
  swapa = swap;
  namesza = namesz;
  descsza = descsz;
  os_style = -1;
  if ( namesz == 4 && !strncmp((const char *)&nbufa[noff], "CORE", 4uLL)
    || namesza == 5 && !strcmp((const char *)&nbufa[noff], "CORE") )
  {
    os_style = 0;
  }
  if ( namesza == 8 && !strcmp((const char *)&nbufa[noff], "FreeBSD") )
    os_style = 1;
  if ( namesza >= 0xB && !strncmp((const char *)&nbufa[noff], "NetBSD-CORE", 0xBuLL) )
    os_style = 2;
  if ( os_style != -1 && (*flags & 0x20) == 0 )
  {
    if ( file_printf(msa, ", %s-style", &os_style_names[8 * os_style]) == -1 )
      return 1;
    *flags |= 0x20u;
    *flags |= os_style;
  }
  if ( os_style == 2 )
  {
    if ( typea == 1 )
    {
      memset(&pi, 0, sizeof(pi));
      memcpy(&pi, &nbufa[doff], descsza);
      v25 = msa;
      v26 = file_printable(sbuf, 0x200uLL, pi.cpi_name);
      v27 = getu32(swapa, pi.cpi_pid);
      v28 = getu32(swapa, pi.cpi_euid);
      v29 = getu32(swapa, pi.cpi_egid);
      v12 = getu32(swapa, pi.cpi_nlwps);
      v13 = getu32(swapa, pi.cpi_siglwp);
      v14 = getu32(swapa, pi.cpi_signo);
      v15 = getu32(swapa, pi.cpi_sigcode);
      if ( file_printf(
             v25,
             ", from '%.31s', pid=%u, uid=%u, gid=%u, nlwps=%u, lwp=%u (signal %u/code %u)",
             v26,
             v27,
             v28,
             v29,
             v12,
             v13,
             v14,
             v15) != -1 )
        *flags |= 4u;
      return 1;
    }
    return 0;
  }
  if ( typea != 3 || (*flags & 0x800) == 0 )
    return 0;
  i = 0LL;
LABEL_26:
  if ( i >= 5 )
    return 0;
  if ( clazz == 1 )
    v24 = *(_QWORD *)&prpsoffsets32[8 * i];
  else
    v24 = prpsoffsets64[i];
  reloffset = v24;
  noffset = v24 + doff;
  for ( j = 0LL; j < 0x10; ++j )
  {
    if ( noffset >= size || reloffset >= descsza )
      goto LABEL_79;
    c = nbufa[noffset];
    if ( !c )
    {
      if ( !j )
      {
LABEL_79:
        ++i;
        goto LABEL_26;
      }
      break;
    }
    if ( ((*__ctype_b_loc())[c] & 0x4000) == 0 || strchr("'\"`", c) )
      goto LABEL_79;
    ++noffset;
    ++reloffset;
  }
  for ( k = i + 1; k < 5; ++k )
  {
    adjust = 1;
    if ( clazz == 1 )
      v23 = *(_QWORD *)&prpsoffsets32[8 * k];
    else
      v23 = prpsoffsets64[k];
    if ( clazz == 1 )
      v22 = *(_QWORD *)&prpsoffsets32[8 * i];
    else
      v22 = prpsoffsets64[i];
    if ( v23 < v22 )
    {
      v21 = clazz == 1 ? *(_QWORD *)&prpsoffsets32[8 * k] : prpsoffsets64[k];
      for ( no = v21 + doff; ; ++no )
      {
        v20 = clazz == 1 ? *(_QWORD *)&prpsoffsets32[8 * i] : prpsoffsets64[i];
        if ( no >= v20 + doff )
          break;
        v19 = 0;
        if ( adjust )
          v19 = ((*__ctype_b_loc())[nbufa[no]] & 0x4000) != 0;
        adjust = v19;
      }
      if ( adjust )
        i = k;
    }
  }
  if ( clazz == 1 )
    v18 = *(_QWORD *)&prpsoffsets32[8 * i];
  else
    v18 = prpsoffsets64[i];
  cname = &nbufa[v18 + doff];
  for ( cp = cname; ; ++cp )
  {
    v17 = 0;
    if ( *cp )
      v17 = ((*__ctype_b_loc())[*cp] & 0x4000) != 0;
    if ( !v17 )
      break;
  }
  while ( 1 )
  {
    v16 = 0;
    if ( cp > cname )
      v16 = ((*__ctype_b_loc())[*(cp - 1)] & 0x2000) != 0;
    if ( !v16 )
      break;
    --cp;
  }
  if ( file_printf(msa, ", from '%.*s'", (_DWORD)cp - (_DWORD)cname, (const char *)cname) != -1 )
    *flags |= 4u;
  return 1;
}