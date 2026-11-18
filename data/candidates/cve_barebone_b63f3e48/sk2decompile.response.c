void DoCommand(char *fname, int verbose) {
  char cmd[12288];
  char tmpfname[4096];
  int gotoutput = 0;
  int cmdlen = 0;
  int i;
  struct stat st;
  struct stat st2;
  struct utimbuf ut;
  for (i = strlen(fname) - 1; i > 0 && fname[i - 1] != '/'; i--)
    ;
  memcpy(tmpfname, fname, i);
  strcpy(tmpfname + i, "XXXXXX");
  mktemp(tmpfname);
  if (tmpfname[0] == '\0') ErrFatal("Cannot find available temporary file name");
  for (i = 0;; i++) {
    if (command[i] == '&') {
      if (command[i + 1] == 'i') {
        cmdlen += shellescape(cmd + cmdlen, fname);
        i++;
        continue;
      }
      if (command[i + 1] == 'o') {
        cmdlen += shellescape(cmd + cmdlen, tmpfname);
        i++;
        gotoutput = 1;
        continue;
      }
    }
    cmd[cmdlen++] = command[i];
    if (command[i] == '\0') break;
  }
  if (verbose) printf("Cmd:%s\n", cmd);
  errno = 0;
  i = system(cmd);
  if (i || errno) {
    if (errno) perror("system");
    ErrFatal("Problem executing specified command");
  }
  if (gotoutput) {
    i = stat(tmpfname, &st2);
    if (i) ErrFatal("specified command did not produce expected output file");
    i = stat(fname, &st);
    unlink(fname);
    rename(tmpfname, fname);
    if (!i) {
      chmod(fname, st.st_mode);
      ut.actime = st.st_atime;
      ut.modtime = st.st_mtime;
      utime(fname, &ut);
    }
  }
}