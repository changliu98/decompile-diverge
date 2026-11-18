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
  NetBSD_elfcore_procinfo pi;
  char sbuf[512];
  int os_style = -1;
  size_t i, j, k;
  size_t reloffset, noffset;
  unsigned __int8 *cname, *cp;
  unsigned __int8 c;

  // Determine OS style based on the note name
  if ((namesz == 4 && !strncmp((const char *)&nbuf[noff], "CORE", 4)) ||
      (namesz == 5 && !strcmp((const char *)&nbuf[noff], "CORE")))
  {
    os_style = 0;
  }
  if (namesz == 8 && !strcmp((const char *)&nbuf[noff], "FreeBSD"))
    os_style = 1;
  if (namesz >= 11 && !strncmp((const char *)&nbuf[noff], "NetBSD-CORE", 11))
    os_style = 2;

  // Print OS style if it hasn't been printed yet
  if (os_style != -1 && (*flags & 0x20) == 0)
  {
    if (file_printf(ms, ", %s-style", &os_style_names[8 * os_style]) == -1)
      return 1;
    *flags |= 0x20;
    *flags |= os_style;
  }

  // Handle NetBSD core notes
  if (os_style == 2)
  {
    if (type == 1)
    {
      char *printable_name;
      uint32_t pid, euid, egid, nlwps, siglwp, signo, sigcode;

      memset(&pi, 0, sizeof(pi));
      memcpy(&pi, &nbuf[doff], descsz);
      
      printable_name = file_printable(sbuf, 0x200, pi.cpi_name);
      pid = getu32(swap, pi.cpi_pid);
      euid = getu32(swap, pi.cpi_euid);
      egid = getu32(swap, pi.cpi_egid);
      nlwps = getu32(swap, pi.cpi_nlwps);
      siglwp = getu32(swap, pi.cpi_siglwp);
      signo = getu32(swap, pi.cpi_signo);
      sigcode = getu32(swap, pi.cpi_sigcode);

      if (file_printf(
             ms,
             ", from '%.31s', pid=%u, uid=%u, gid=%u, nlwps=%u, lwp=%u (signal %u/code %u)",
             printable_name, pid, euid, egid, nlwps, siglwp, signo, sigcode) != -1)
      {
        *flags |= 4;
      }
      return 1;
    }
    return 0;
  }

  // Handle other OS styles
  if (type != 3 || (*flags & 0x800) == 0)
    return 0;

  for (i = 0; i < 5; ++i)
  {
    size_t offset_i = (clazz == 1) ? prpsoffsets32[i] : prpsoffsets64[i];
    reloffset = offset_i;
    noffset = offset_i + doff;

    for (j = 0; j < 16; ++j)
    {
      if (noffset >= size || reloffset >= descsz)
        break;
      
      c = nbuf[noffset];
      if (!c)
      {
        if (!j)
          break; // goto next i
        break;
      }
      
      if (((*__ctype_b_loc())[c] & 0x4000) == 0 || strchr("'\"`", c))
        break; // goto next i
      
      ++noffset;
      ++reloffset;
    }

    // If the inner loop broke early due to invalid chars or boundaries, skip to next `i`
    if (j != 16 && (noffset >= size || reloffset >= descsz || c == 0 || ((*__ctype_b_loc())[c] & 0x4000) == 0 || strchr("'\"`", c)))
    {
      if (j == 0 && (noffset >= size || reloffset >= descsz || c == 0 || ((*__ctype_b_loc())[c] & 0x4000) == 0 || strchr("'\"`", c)))
        continue;
    }

    // Find the best valid string block
    for (k = i + 1; k < 5; ++k)
    {
      size_t offset_k = (clazz == 1) ? prpsoffsets32[k] : prpsoffsets64[k];
      if (offset_k < offset_i)
      {
        int adjust = 1;
        size_t no;
        for (no = offset_k + doff; no < offset_i + doff; ++no)
        {
          if (adjust)
            adjust = ((*__ctype_b_loc())[nbuf[no]] & 0x4000) != 0;
        }
        if (adjust)
          i = k;
      }
    }

    // Extract and trim the command name
    size_t final_offset = (clazz == 1) ? prpsoffsets32[i] : prpsoffsets64[i];
    cname = &nbuf[final_offset + doff];
    
    for (cp = cname; *cp && ((*__ctype_b_loc())[*cp] & 0x4000) != 0; ++cp)
      ;

    while (cp > cname && ((*__ctype_b_loc())[*(cp - 1)] & 0x2000) != 0)
      --cp;

    if (file_printf(ms, ", from '%.*s'", (int)(cp - cname), (const char *)cname) != -1)
      *flags |= 4;

    return 1;
  }

  return 0;
}