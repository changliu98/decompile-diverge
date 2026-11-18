static void listdir(int depth, int fd, struct clientinfo *clntinfo, char *dir)
{
 struct fileinfo *fi, *fis;
 char *buf, *dirs;

 if (depth >= max_ls_depth || matches >= max_ls_files) {
  return;
 }

 dirs = sreaddir(&buf);
 if (dirs == NULL) {
  addreply(226, "Sorry, we were unable to read [%s]", dir);
  return;
 }

 for (fi = fis = (struct fileinfo *)dirs; fi->len != (size_t)-1; fi++) {
  int ok = 0;

  switch (fi->name[fi->len]) {
  case '\0':
   ok = listfile(fi, NULL);
   break;
  case '.':
   if (!opt_a)
    break;
   if (fi->name[fi->len + 1] == '\0' ||
       (fi->name[fi->len + 1] == '.' &&
        fi->name[fi->len + 2] == '\0')) {
    ok = listfile(fi, NULL);
   } else {
    ok = listfile(fi, NULL);
   }
   break;
  default:
   ok = listfile(fi, NULL);
  }
  if (!ok) {
   fi->len = (size_t)-1;
  }
 }

 outputfiles(fd, clntinfo);

 for (fi = fis; ; fi = (struct fileinfo *)((char *)fi + sizeof(struct fileinfo))) {
  char c = opt_R ? (fi != fis) : 0;

  if (!(c & 1))
   continue;

  if (fi->len == (size_t)-1)
   continue;

  if (chdir(fi->name + fi->len) != 0)
   continue;

  {
   char subdir[4096 + 1];

   if (subdir == NULL) {
    toomany();
    goto done;
   }
   if (snprintf(subdir, sizeof(subdir), "%s/%s",
         dir, fi->name + fi->len) >= sizeof(subdir)) {
    nolist();
    goto done;
   }
  }

  wrstr(fd, clntinfo, "\r\n\r\n");
  wrstr(fd, clntinfo, subdir);
  wrstr(fd, clntinfo, ":");
  listdir(depth + 1, fd, clntinfo, subdir);

done:
  if (matches >= max_ls_files) {
   toomany();
   goto done;
  }
  if (chdir("..") != 0) {
   if (chdir(wd) != 0 || chdir(dir) != 0) {
    die(421, 3, "chdir: %s",
        strerror(*___errno_location()));
   }
  }
 }
free:
 free(buf);
 free(fis);
 buf = NULL;
}