void listdir(unsigned depth, int fd, char **pptr, const char *path) {
  char *buf;
  struct dirent *dir, *d, *end;
  if (depth >= maxdepth || nfiles >= maxfiles) return;
  dir = sreaddir(&buf);
  if (!dir) {
    addreply(226, "Sorry, we were unable to read [%s]", path);
    return;
  }
  for (d = dir; d->d_off != (unsigned long)-1; d++) {
    int rc = 0;
    if (d->d_name[d->d_off] == '.') {
      if (listhidden) {
        if (d->d_name[d->d_off + 1] == '\0' ||
            (d->d_name[d->d_off + 1] == '.' &&
             d->d_name[d->d_off + 2] == '\0')) {
          listfile(d, 0);
        } else {
          rc = listfile(d, 0);
        }
      }
      if (!rc) d->d_off = (unsigned long)-1;
    } else {
      rc = listfile(d, 0);
    }
  }
  outputfiles(fd, pptr);
  for (d = dir; listsubdirs && d != end; d++) {
    if (d->d_off != (unsigned long)-1) {
      if (!chdir(d->d_name + d->d_off)) {
        char newpath[4096 + 1];
        if (snprintf(newpath, sizeof(newpath), "%s/%s", path,
                     d->d_name + d->d_off) < (int)sizeof(newpath)) {
          wrstr(fd, pptr, "\r\n\r\n");
          wrstr(fd, pptr, newpath);
          wrstr(fd, pptr, ":\r\n\r\n");
          listdir(depth + 1, fd, pptr, newpath);
        }
        if (nfiles >= maxfiles) break;
        if (!chdir("..") || (!chdir(cwd) && !chdir(path))) continue;
        die(421, 3, "chdir: %s", strerror(errno));
      }
    }
  }
  free(buf);
  free(dir);
}