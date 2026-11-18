void cwk_path_get_root_windows(char *path,size_t *length)

{
  _Bool _Var1;
  _Bool local_22;
  _Bool is_device_path;
  char *c;
  size_t *length_local;
  char *path_local;
  
  *length = 0;
  if (*path != '\0') {
    _Var1 = cwk_path_is_separator(path);
    if (_Var1) {
      _Var1 = cwk_path_is_separator(path + 1);
      if (_Var1) {
        c = path + 2;
        if ((*c == '?') || (local_22 = false, *c == '.')) {
          c = path + 3;
          local_22 = cwk_path_is_separator(c);
        }
        if (local_22 == false) {
          c = cwk_path_find_next_stop(c);
          while (_Var1 = cwk_path_is_separator(c), _Var1) {
            c = c + 1;
          }
          c = cwk_path_find_next_stop(c);
          _Var1 = cwk_path_is_separator(c);
          if (_Var1) {
            c = c + 1;
          }
          *length = (long)c - (long)path;
        }
        else {
          *length = 4;
        }
      }
      else {
        *length = *length + 1;
      }
    }
    else if (path[1] == ':') {
      *length = 2;
      _Var1 = cwk_path_is_separator(path + 2);
      if (_Var1) {
        *length = 3;
      }
    }
  }
  return;
}