void cwk_path_fix_root(char *buffer,size_t buffer_size,size_t length)

{
  _Bool _Var1;
  size_t i;
  size_t length_local;
  size_t buffer_size_local;
  char *buffer_local;
  
  if (path_style == CWK_STYLE_WINDOWS) {
    length_local = length;
    if (buffer_size < length) {
      length_local = buffer_size;
    }
    for (i = 0; i < length_local; i = i + 1) {
      _Var1 = cwk_path_is_separator(buffer + i);
      if (_Var1) {
        buffer[i] = *separators[0];
      }
    }
  }
  return;
}