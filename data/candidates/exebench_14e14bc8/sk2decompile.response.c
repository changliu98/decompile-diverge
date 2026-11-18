void c_sysconf_(int *name, long *value, int *ierr) {
  *value = sysconf(*name);
  *ierr = errno;
  return;
}