char *mdir_name(char *path)
{
 char *new_path;
 size_t len = dir_len(path);
 char append_dot = 1;

 if (len != 0) {
  append_dot = 0;
 } else {
  len = 1;
 }

 new_path = malloc(len + append_dot + 1);
 if (new_path == NULL) {
  return NULL;
 }
 memcpy(new_path, path, len);

 if (append_dot) {
  new_path[len++] = '.';
 }

 new_path[len] = '\0';
 return new_path;
}