int
do_core_note(struct magic_set *ms, const unsigned char *buf, uint32_t type,
 int swap, uint32_t namesz, uint32_t descsz, uint32_t noff, uint32_t doff,
 int *flags, uint32_t size, int clazz)
{
 uint32_t i, j, k, off, adjust;
 const char *p, *q;
 char sbuf[512];
 int os_style = -1;







 if (namesz == sizeof("CORE") &&
     !strncmp((const char *)buf + noff, "CORE", sizeof("CORE") - 1))
  os_style = 0;

 if (namesz == sizeof("CORE") &&
     !strcmp((const char *)buf + noff, "CORE"))
  os_style = 0;

 if (namesz == sizeof("FreeBSD") &&
     !strcmp((const char *)buf + noff, "FreeBSD"))
  os_style = 1;

 if (namesz >= sizeof("NetBSD-CORE") &&
     !strncmp((const char *)buf + noff, "NetBSD-CORE", sizeof("NetBSD-CORE") - 1))
  os_style = 2;

 if (os_style != -1 && !(*flags & 0x20)) {
  if (file_printf(ms, ", %s-style", os_style_names + os_style) == -1)
   return 1;
  *flags |= 0x20;
  *flags |= os_style;
 }

 if (os_style == 2 && type == 1) {
  NetBSD_elfcore_procinfo pi;
  memset(&pi, 0, sizeof(pi));
  memcpy(&pi, buf + doff, descsz);
  p = file_printable(sbuf, sizeof(sbuf), pi.cpi_name);
  if (file_printf(ms,
      ", from '%.31s', pid=%u, uid=%u, gid=%u, nlwps=%u, "
      "lwp=%u (signal %u/code %u)",
      p,
      getu32(swap, pi.cpi_pid),
      getu32(swap, pi.cpi_euid),
      getu32(swap, pi.cpi_egid),
      getu32(swap, pi.cpi_nlwps),
      getu32(swap, pi.cpi_siglwp),
      getu32(swap, pi.cpi_signo),
      getu32(swap, pi.cpi_sigcode)) == -1)
   return 1;
  *flags |= 0x04;
  return 1;
 }







 if (type != 3 || !(*flags & 0x800))
  return 0;

 for (i = 0; i < 5; i++) {
  off = (clazz == 1 ? prpsoffsets32[i] : prpsoffsets64[i]);
  for (j = 0; j < 16; j++) {
   if (doff + off >= size || off >= descsz)
    break;
   if (buf[doff + off] == '\0')
    break;
   if (!((__ctype_b_loc ())->__ctype_b[buf[doff + off]] & 0x4000))
    break;
   if (strchr("\'\"`", buf[doff + off]))
    break;
   off++;
  }
  if (j > 0) {
   for (k = i + 1; k < 5; k++) {
    if ((clazz == 1 ? prpsoffsets32[k] : prpsoffsets64[k]) < (clazz == 1 ? prpsoffsets32[i] : prpsoffsets64[i])) {
     int white = 1;
     for (off = (clazz == 1 ? prpsoffsets32[k] : prpsoffsets64[