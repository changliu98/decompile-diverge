static int do_core_note(struct magic_set *ms, unsigned char *buf, int n,
                        int swap, unsigned magiclen, unsigned len,
                        unsigned magic, unsigned note, unsigned *flags,
                        unsigned maxlen, unsigned arch) {
  int core_style = -1;
  if ((magiclen == 4 && !strncmp((char *)buf + magic, "CORE", 4)) ||
      (magiclen == 5 && !strcmp((char *)buf + magic, "CORE")))
    core_style = 0;
  if (magiclen == 8 && !strcmp((char *)buf + magic, "FreeBSD")) core_style = 1;
  if (magiclen >= 11 && !strncmp((char *)buf + magic, "NetBSD-CORE", 11))
    core_style = 2;
  if (core_style != -1 && !(*flags & 0x00000020)) {
    if (file_printf(ms, ", %s-style", core_style_names[core_style]) == -1)
      return (1);
    *flags |= 0x00000020;
    *flags |= core_style;
  }
  if (core_style == 2) {
    if (n == 1) {
      char name[512];
      struct core_note_1 note1;
      memset(&note1, 0, sizeof(note1));
      memcpy(&note1, buf + note, len);
      if (file_printf(ms,
                      ", from '%.31s', pid=%u, uid=%u, gid=%u, nlwps=%u, "
                      "lwp=%u (signal %u/code %u)",
                      file_printable(name, sizeof(name), note1.cn_name),
                      getu32(swap, note1.cn_pid), getu32(swap, note1.cn_uid),
                      getu32(swap, note1.cn_gid), getu32(swap, note1.cn_nlwps),
                      getu32(swap, note1.cn_lwp),
                      getu32(swap, note1.cn_sig),
                      getu32(swap, note1.cn_code)) == -1)
        return (1);
      *flags |= 0x00000004;
      return (1);
    }
    return (0);
  }
  if (n == 3 && (*flags & 0x00000800)) {
    unsigned i, j, k, l;
    unsigned off, off2;
    unsigned char *p, *q;
    for (i = 0; i < 5; i++) {
      off = arch == 1 ? core_note_offsets_32[i] : core_note_offsets_64[i];
      off2 = off + note;
      for (j = 0; j < 16; j++) {
        unsigned char c;
        if (off2 >= maxlen || off >= len) goto next;
        c = buf[off2];
        if (c == '\0') {
          if (j == 0) goto next;
          break;
        }
        if (!isprint(c) || strchr("'\"`", c) != NULL) goto next;
        off2++;
        off++;
      }
      for (k = i + 1; k < 5; k++) {
        int skip = 1;
        off = arch == 1 ? core_note_offsets_32[k] : core_note_offsets_64[k];
        off2 = off + note;
        off = arch == 1 ? core_note_offsets_32[i] : core_note_offsets_64[i];
        if (off < off2) {
          off = arch == 1 ? core_note_offsets_32[k] : core_note_offsets_64[k];
          for (l = off + note; l < off + note; l++) {
            if (skip && isprint(buf[l])) skip = 0;
          }
          if (skip) i = k;
        }
      }
      p = q = buf + (arch == 1 ? core_note_offsets_32[i]
                               : core_note_offsets_64[i]) +
              note;
      while (*p && isprint(*p)) p++;
      while (p > q && isspace(p[-1])) p--;
      if (file_printf(ms, ", from '%.*s'", (int)(p - q), q) == -1) return (1);
      *flags |= 0x00000004;
      return (1);
    next:;
    }
  }
  return (0);
}