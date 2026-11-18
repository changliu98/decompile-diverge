void ddelete_c(char *filename, int *ierr) {
  int i;
  i = unlink(filename);
  if (i == 0) {
    *ierr = 0;
  } else {
    *ierr = errno;
  }
}