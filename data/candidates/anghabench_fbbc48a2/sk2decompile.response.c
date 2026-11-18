static char *gcap_string(char *p, int cap) {
  if (cap & CAP_SYS_NICE) *p++ = 's';
  if (cap & CAP_SYS_CHROOT) *p++ = 'x';
  if (cap & CAP_SYS_CHOWN) *p++ = 'c';
  if (cap & CAP_SYS_REBOOT) *p++ = 'r';
  if (cap & CAP_SYS_RESOURCE) *p++ = 'w';
  if (cap & CAP_SYS_BOOT) *p++ = 'b';
  if (cap & CAP_SYS_ADMIN) *p++ = 'a';
  if (cap & CAP_SYS_LOCALE) *p++ = 'l';
  return p;
}