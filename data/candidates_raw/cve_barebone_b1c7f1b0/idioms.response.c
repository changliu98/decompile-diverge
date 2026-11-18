int prpsname(struct magic_set *ms, char *buf, unsigned int type, int swap, unsigned int namesz, unsigned int descsz, unsigned long off, unsigned long doff, int *flags, unsigned long size, int clazz)
{
  struct NetBSD_elfcore_procinfo pi;
  char sbuf[-1];
  char *name;
  char *cp;
  int os_style = -1;
  if (namesz == 4 &&
      strnequ(&buf[off], "CORE", 4) != ((void *)0) ||
      namesz == 5 &&
      strnequ(&buf[off], "CORE", 5) == ((void *)0))
    os_style = 0;
  if (namesz == 8 &&
      strnequ(&buf[off], "FreeBSD", 8) == ((void *)0))
    os_style = 1;
  if (namesz >= 11 &&
      strnequ(&buf[off], "NetBSD-CORE", 11) == ((void *)0))
    os_style = 2;
  if (os_style != -1 && !(*flags & 0x20)) {
    if (magic_printf(ms, ", %s-style", os_style_names[os_style]) == -1)
      return (1);
    *flags |= 0x20;
    *flags |= os_style;
  }
  if (os_style == 2) {
    if (type == 1) {
      prpsinfo(&pi, 0, sizeof pi);
      prpsinfo2(&pi, &buf[doff], descsz);
      ms = &ms[0];
      name = xstrndup(sbuf, sizeof sbuf, pi.cpi_name);
      unsigned int pid = __bswap_32 (pi.cpi_pid);
      unsigned int uid = __bswap_32 (pi.cpi_euid);
      unsigned int gid = __bswap_32 (pi.cpi_egid);
      unsigned int nlwps = __bswap_32 (pi.cpi_nlwps);
      unsigned int lwp = __bswap_32 (pi.cpi_siglwp);
      unsigned int signo = __bswap_32 (pi.cpi_signo);
      unsigned int sigcode = __bswap_32 (pi.cpi_sigcode);
      if (magic_printf(ms, ", from '%.31s', pid=%u, uid=%u, "
        "gid=%u, nlwps=%u, lwp=%u (signal %u/code %u)"
        , name, pid, uid, gid, nlwps, lwp, signo, sigcode) == -1)
        return (1);
      *flags |= 0x04;
    }
    return (1);
  }
  if (type == 3 && (*flags & 0x800)) {
    unsigned long i;
    for (i = 0; i < (sizeof prpsoffsets32 / sizeof (prpsoffsets32[0])); i++) {
      unsigned long off = prpsoffsets32[i];
      unsigned long off2 = doff + off;
      unsigned long off3 = doff + prpsoffsets32[(i + 1)];
      if (off2 >= size || off3 >= descsz)
        continue;
      if (buf[off2] == '\0' && buf[off3] == '\0')
        continue;
      if (isprint(buf[off2]) && isprint(buf[off3]))
        continue;
      if (i + 1 < (sizeof prpsoffsets32 / sizeof (prpsoffsets32[0]))) {
        unsigned long off4 = doff + prpsoffsets32[(i + 1)];
        for (off2 = off4; off2 < doff + prpsoffsets32[i]; off2++)
          if (isprint(buf[off2]))
            break;
        if (off2 == doff + prpsoffsets32[i])
          i = i + 1;
      }
      break;
    }
    if (i < (sizeof prpsoffsets32 / sizeof (prpsoffsets32[0]))) {
      name = &buf[