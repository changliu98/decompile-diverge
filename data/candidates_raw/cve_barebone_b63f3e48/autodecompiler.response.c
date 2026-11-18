static void apply_filter(char *filename, int verbose)
{
    char tmpname[4096 + 1];
    char cmd[12000 + 1];
    struct stat st;
    struct stat stt;
    struct utimbuf ut;
    int i, j, k, ret, tmpused = 0;

    j = 0;
    for (k = strlen(filename) - 1;; k--) {
 if (k <= 0 || filename[k - 1] == '/') break;
    }
    memcpy(tmpname, filename, k);
    strcpy(tmpname + k, "XXXXXX");
    mktemp(tmpname);
    if (tmpname[0] == '\0') {
 ErrFatal("Cannot find available temporary file name");
    }

    j = 0;
    for (i = 0;; i++) {
 switch (ApplyCommand[i]) {
 case '&':
     switch (ApplyCommand[i + 1]) {
     case 'i':
  j += shellescape(cmd + j, filename);
  i++;
  break;
     case 'o':
  j += shellescape(cmd + j, tmpname);
  i++;
  tmpused = 1;
  break;
     default:
  break;
     }
     break;
 default:
     cmd[j++] = ApplyCommand[i];
     if (ApplyCommand[i] == '\0') break;
     break;
 }
    }

    if (verbose) printf("Cmd:%s\n", cmd);

    *___errno_location() = 0;
    ret = system(cmd);
    if (ret != 0 || *___errno_location() != 0) {
 if (*___errno_location() != 0) perror("system");
 ErrFatal("Problem executing specified command");
    }

    if (tmpused) {
 if (_stat(tmpname, &stt) == 0) {
     ret = _stat(filename, &st);
     unlink(filename);
     rename(tmpname, filename);
     if (ret == 0) {
  chmod(filename, st.st_mode);
  ut.actime = st.st_atime;
  ut.modtime = st.st_mtime;
  utime(filename, &ut);
     }
 } else {
     ErrFatal("specified command did not produce expected output file");
 }
    }
}