void file_perms_get(const char *filename, int *uid, int *perms) {
  struct stat st;
  if (uid && *uid) *uid = 0;
  if (perms && *perms) *perms = 0;
  if (stat(filename, &st) < 0) return;
  if (uid) *uid = st.st_uid;
  if (perms) *perms = st.st_mode & 07777;
}