OS_RESULT OS_file_open(OS_FILE *fd, char *name) {
  *fd = open(name, 0);
  if (*fd == (OS_FILE)-1) {
    return (0x1004);
  }
  return (0x0000);
}